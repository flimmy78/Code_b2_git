#include "stdafx.h"
#include "DemoKeygen.h"


std::string DemoKeygen::generate_key()
{
    if ( m_serial_number.empty() )
    {
        m_serial_number = get_physical_drive_serial_number();
    }

    return md5( create_machine_code( m_serial_number ) );
}


std::string DemoKeygen::get_physical_drive_serial_number( int drive_number )
{
    // Format physical drive path (may be '\\.\PhysicalDrive0', '\\.\PhysicalDrive1' and so on).
    CString strDrivePath;
    strDrivePath.Format( _T("\\\\.\\PhysicalDrive%u"), drive_number );

    // 2. Set the default process security level
    // http://msdn.microsoft.com/en-us/library/windows/desktop/aa393617(v=vs.85).aspx
    HRESULT hr =  ::CoInitializeSecurity(
        NULL,                        // Security descriptor
        -1,                          // COM negotiates authentication service
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication level for proxies
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation level for proxies
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities of the client or server
        NULL);                       // Reserved
    ATLENSURE_SUCCEEDED(hr);

    // 3. Create a connection to WMI namespace
    // http://msdn.microsoft.com/en-us/library/windows/desktop/aa389749(v=vs.85).aspx

    // 3.1. Initialize the IWbemLocator interface
    CComPtr<IWbemLocator> pIWbemLocator;
    hr = ::CoCreateInstance( CLSID_WbemLocator, 0,  CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pIWbemLocator );
    ATLENSURE_SUCCEEDED(hr);

    // 3.2. Call IWbemLocator::ConnectServer for connecting to WMI
    CComPtr<IWbemServices> pIWbemServices;
    hr = pIWbemLocator->ConnectServer( L"ROOT\\CIMV2", NULL, NULL, 0, NULL, 0, 0, &pIWbemServices );
    ATLENSURE_SUCCEEDED(hr);

    // 4. Set the security levels on WMI connection
    // http://msdn.microsoft.com/en-us/library/windows/desktop/aa393619(v=vs.85).aspx
    hr = ::CoSetProxyBlanket(
        pIWbemServices,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE);
    ATLENSURE_SUCCEEDED(hr);

    // 5. Execute a WQL (WMI Query Language) query to get physical media info
    const BSTR szQueryLanguage = L"WQL";
    const BSTR szQuery =  L"SELECT Tag, SerialNumber FROM Win32_PhysicalMedia";
    CComPtr<IEnumWbemClassObject> pIEnumWbemClassObject;
    hr = pIWbemServices->ExecQuery(
        szQueryLanguage,                                       // Query language
        szQuery,                                               // Query
        WBEM_FLAG_FORWARD_ONLY|WBEM_FLAG_RETURN_IMMEDIATELY,   // Flags
        NULL,                                                  // Context
        &pIEnumWbemClassObject);                               // Enumerator
    ATLENSURE_SUCCEEDED(hr);

    // 6. Get each enumerator element until find the desired physical drive
    ULONG uReturn = 0;

    while ( pIEnumWbemClassObject )
    {
        CComPtr<IWbemClassObject> pIWbemClassObject;
        hr = pIEnumWbemClassObject->Next( WBEM_INFINITE, 1, &pIWbemClassObject, &uReturn );

        if ( 0 == uReturn || FAILED(hr) )
        {
            break;
        }

        variant_t vtTag;           // unique tag, e.g. '\\.\PHYSICALDRIVE0'
        variant_t vtSerialNumber;  // manufacturer-provided serial number

        hr = pIWbemClassObject->Get( L"Tag", 0, &vtTag, NULL, NULL );
        ATLENSURE_SUCCEEDED(hr);

        CString strTag( vtTag.bstrVal );

        if ( !strTag.CompareNoCase(strDrivePath) ) // physical drive found
        {
            hr = pIWbemClassObject->Get( L"SerialNumber", 0, &vtSerialNumber, NULL, NULL );
            ATLENSURE_SUCCEEDED(hr);
            CString strSerialNumber;
            strSerialNumber = vtSerialNumber.bstrVal; // get the serial number
            strSerialNumber.Trim();
            return (const char*)strSerialNumber;
        }
    }

    throw std::runtime_error( "failed to get physical drive serial number." );
    return "";
}


std::string DemoKeygen::create_machine_code( const std::string& serial_number )
{
    return "TRANSACTIVE-MACHINE-CODE: " + serial_number;
}


void DemoKeygen::save_key_to_file( const std::string& key, const std::string& file_name )
{
    boost::filesystem::path parent = boost::filesystem::path(file_name).parent_path();

    if ( !boost::filesystem::exists( parent ) )
    {
        boost::system::error_code ec;
        boost::filesystem::create_directories( parent, ec );
    }

    std::ofstream os( file_name.c_str() );

    if ( !os )
    {
        std::stringstream strm;
        strm << "can not open '" << file_name << "' for writing.";
        throw std::runtime_error( strm.str() );
    }

    os << key;
    if ( m_message ) { std::cout << "key-file: " << file_name << std::endl; }
}


std::string DemoKeygen::get_key_from_file( const std::string& file_name )
{
    std::ofstream is( file_name.c_str() );

    if ( !is )
    {
        std::stringstream strm;
        strm << "can not open '" << file_name << "' for reading.";
        throw std::runtime_error( strm.str() );
    }

    std::stringstream strm;
    strm << is.rdbuf();
    return strm.str();
}


std::string DemoKeygen::md5( const std::string& str )
{
    const size_t MD5LEN = 16;
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    BYTE rgbHash[MD5LEN];
    DWORD cbHash = MD5LEN;
    CHAR rgbDigits[] = "0123456789abcdef";
    std::stringstream strm;

    if ( CryptAcquireContext( &hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT ) &&
         CryptCreateHash( hProv, CALG_MD5, 0, 0, &hHash ) &&
         CryptHashData( hHash, (BYTE*)str.c_str(), str.size(), 0 ) &&
         CryptGetHashParam( hHash, HP_HASHVAL, rgbHash, &cbHash, 0 ) )
    {
        for ( size_t i = 0; i < cbHash; i++ )
        {
            strm << rgbDigits[rgbHash[i] >> 4] << rgbDigits[rgbHash[i] & 0xf];
        }
    }

    if ( hHash )
    {
        CryptDestroyHash(hHash);
    }

    if ( hProv )
    {
        CryptReleaseContext(hProv, 0);
    }

    std::string md5_key = strm.str();

    if ( md5_key.empty() )
    {
        throw std::runtime_error( "failed to create md5 key" );
    }

    return md5_key;
}
