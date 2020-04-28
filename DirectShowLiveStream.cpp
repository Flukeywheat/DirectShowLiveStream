#include <dshow.h>

int main()
{
    IGraphBuilder* pGraph;
    IMediaControl* pControl;
    IMediaEvent* pEvent;

    HRESULT Hr = CoInitialize(NULL);
    if (FAILED(Hr))
    {
        printf("Error initializing COM Library");
        return 0;
    }

    Hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
    if (FAILED(Hr))
    {
        printf("Error creating FilterGraph Manager");
        return 0;
    }


    Hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
    Hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
    
    //      Video File
    //Hr = pGraph->RenderFile(L"C:/Users/chapt/Music/DirectShow.mp4", NULL);

    //      Audio File
    Hr = pGraph->RenderFile(L"C:/Users/chapt/Music/Roto.wav", NULL); 

    if (SUCCEEDED(Hr))
    {
        Hr = pControl->Run();

        if (SUCCEEDED(Hr))
        {
            long evCode = 0;
            pEvent->WaitForCompletion(INFINITE, &evCode);
        }
    }

    pControl->Release();
    pEvent->Release();
    pGraph->Release();
    CoUninitialize();

}

