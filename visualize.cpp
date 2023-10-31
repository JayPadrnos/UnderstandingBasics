#define UNICODE
#define _UNICODE


#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>


int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    // TODO creates window
    // Step 1 Register a window class
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MusicVisualizerClass";
    RegisterClass(&wc);

    // Step 2: Create a window
    HWND hwnd = CreateWindow(L"MusicVisualizerClass", L"Music Visualizer",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

     // Step 3: Show and update the window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    IMFSourceResolver* pSourceResolver = NULL;
    IMFByteStream* pByteStream = NULL;
    IMFMediaSource* pMediaSource = NULL;
    IPropertyStore* pPropertyStore = NULL;

     HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (SUCCEEDED(hr)) {
        hr = MFStartup(MF_VERSION);
    }

    HRESULT hr = PSCreateMemoryPropertyStore(IID_PPV_ARGS(&pPropertyStore));
    if (SUCCEEDED(hr)) {
        // Property store created successfully.
    }


// Source resolver
hr = MFCreateSourceResolver(&pSourceResolver);
    if (SUCCEEDED(hr)) {
        // Resolve the URL to the media source
        // Set up Attributes with the required attributes
        IMFAttributes* attributes = NULL;
        hr = MFCreateAttributes(&attributes, 1);
        if (SUCCEEDED(hr)) {
            // Set Attributes here, if needed
            // For example, to specify a source resolver, you can set an attribute like this:
            // hr = pPropertyStore->SetValue(MF_PD_PWPHOST_CONTEXT,  pSourceResolver);

            // Resolve the URL to the media source
        hr = pSourceResolver->CreateObjectFromURL(L"your_audio.mp3", MF_RESOLUTION_MEDIASOURCE, pPropertyStore, NULL, NULL, &pMediaSource);
        pPropertyStore->Release(); // Release the property store when done
    } 
}

    // Assuming you have a custom resolver object in pSourceResolver
    hr = pPropertyStore->SetValue(MF_PD_PMPHOST_CONTEXT, pSourceResolver);
    if (SUCCEEDED(hr)) {
        // Attribute set successfully.
    }

IMFSourceReader* pReader = NULL;
hr = MFCreateSourceReaderFromMediaSource(pMediaSource, NULL, &pReader);

//Loop to read audio samples and perform analysis
// ........

// Clean up
pReader->Release();
pMediaSource->Release();
pSourceResolver->Release();

MFShutdown();
CoUninitialize();

    // Step 4: Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
