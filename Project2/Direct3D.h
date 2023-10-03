#pragma once

#include "framework.h"
#include <d3d11.h>
//#include <d3dx11.h>
//#include <d3dx10.h>

// �]�tDirect3D�w���
//#pragma comment (lib, "d3d11.lib")
//#pragma comment (lib, "d3dx11.lib")
//#pragma comment (lib, "d3dx10.lib")

// Direct3D��l��
IDXGISwapChain* swapchain; // ���V�洫�s���f�����w
ID3D11Device* dev; // ���VDirect3D�˸m���������w
ID3D11DeviceContext* devcon; // ���VDirect3D�˸m�W�U�媺���w
ID3D11RenderTargetView* backbuffer;

// ø�Ϭ���
ID3D11InputLayout* pLayout;            // ���V��J�G�������w
ID3D11VertexShader* pVS;               // ���V���I�ۦ⾹�����w
ID3D11PixelShader* pPS;                // ���V�����ۦ⾹�����w
ID3D11Buffer* pVBuffer;                // ���V���I�w�İϪ����w

/* //�]�L�ϥ�3Dø��, ����
// ���ղ`��ø��
// �`��ø��
// ��]�O �w�гy�����s�b3Dø�ϫ�|�Q�л\,���s�b�����|���,
// �i��O�S���A���I�sWM_PAINT,���ѩ�w�ϥ�2Dø�ϧ����ت�,�G3Dø�ϥH�β`��ø�ϼȤ��ϥ�.
ID3D11Texture2D* depthStencilBuffer ;  // �w�İ�
ID3D11DepthStencilView* depthStencilView ;
ID3D11DepthStencilState* depthStencilState ;

struct VERTEX { FLOAT X, Y, Z; D3DXCOLOR Color; };//�w�q��@���I�����c��
*/

void InitD3D(HWND hWnd); // �]�w�ê�l��Direct3D
void RenderFrame(void);
void CleanD3D(void); // ����Direct3D�����񤺦s
void InitGraphics(void);    // �إ߭n��V���Ϊ�
void InitPipeline(void);    // ���J�÷ǳƵۦ⾹

/*
// ��l�ƨ÷ǳ�Direct3D�H�Ѩϥ�
void InitD3D(HWND hWnd)
{
    // �إߤ@�ӵ��c��ӫO�s�����洫�쪺�H��
    DXGI_SWAP_CHAIN_DESC scd;


    // �M�ųo�ӵ��c��H�Ѩϥ�
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // ��g�洫��y�z���c
    scd.BufferCount = 1; // �@�ӫ�w�İ�
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // �ϥ�32�줸��
    scd.BufferDesc.Width = SCREEN_WIDTH;                 // �]�w��w�İϼe��
    scd.BufferDesc.Height = SCREEN_HEIGHT;               // �]�w��w�İϰ���
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // �洫��p��ϥ�
    scd.OutputWindow = hWnd;                             // �n�ϥΪ�����
    scd.SampleDesc.Count = 4;                            // �h�����˪��ƶq
//    scd.SampleDesc.Quality = 0;                          // �h�˥��~�����
    scd.Windowed = TRUE; // �������ù��Ҧ�
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // ���\���ù�����

    // �ϥ�scd���c������T�ӫإ߸˸m�B�˸m�W�U��M�洫��
    D3D11CreateDeviceAndSwapChain(NULL,
                                  D3D_DRIVER_TYPE_HARDWARE,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  D3D11_SDK_VERSION,
                                  &scd,
                                  &swapchain,
                                  &dev,
                                  NULL,
                                  &devcon);

    // ���o��x�w�İϪ���}
    ID3D11Texture2D* pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // �ϥΫ�x�w�İϦ�}�إߴ�V�ؼ�
    dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    pBackBuffer->Release();

    // �N��V�ؼг]�w����x�w�İ�
    devcon->OMSetRenderTargets(1, &backbuffer, NULL);


    // �]�w���f
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = SCREEN_WIDTH;
    viewport.Height = SCREEN_HEIGHT;

    devcon->RSSetViewports(1, &viewport);

    D3D11_TEXTURE2D_DESC depthStencilDesc;
    depthStencilDesc.Width = SCREEN_WIDTH;
    depthStencilDesc.Height = SCREEN_HEIGHT;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    dev->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
    dev->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
    devcon->OMSetRenderTargets(1, &backbuffer, depthStencilView);

    InitPipeline();
    InitGraphics();
}

//��V��@�V
void RenderFrame(void)
{
    // �N��w�İϲM�����`�Ŧ�
    devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

    // �b�o�̶i���w�İϤW��3D��V
    // ��ܭn��ܪ����I�w�İ�
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;
    devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

    // ��ܧڭ̥��b�ϥΪ���l����
    devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // �N���I�w�İ�ø�s���x�w�İ�
    devcon->Draw(3, 0);
    // ������w�İϻP�e�w�İ�
    swapchain->Present(0, 0);
    // �`��ø��
    devcon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

    //�b��ø�s���s�i�H���,���|�L�׮��O�į�
    //Load_Button = CreateWindow(
    //    L"BUTTON",             // ���s��������O�W��
    //    L"Load",               // ���s�W��ܪ���r
    //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // ���s�˦�
    //    10, 10, 100, 30,        // ���s��m�M�j�p (x, y, width, height)
    //    hWnd,                  // �����f�y�`
    //    (HMENU)1,              // ��� ID (�i�H�Ω��ѧO���s)
    //    GetModuleHandle(NULL), // �Ҳեy�`
    //    NULL                   // ���w�� NULL
    //);
    //SetWindowPos(Load_Button, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    //Clean_Button = CreateWindow(
    //    L"BUTTON",             // ���s��������O�W��
    //    L"Clean",              // ���s�W��ܪ���r
    //    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // ���s�˦�
    //    120, 10, 100, 30,        // ���s��m�M�j�p (x, y, width, height)
    //    hWnd,                  // �����f�y�`
    //    (HMENU)2,              // ��� ID (�i�H�Ω��ѧO���s)
    //    GetModuleHandle(NULL), // �Ҳեy�`
    //    NULL                   // ���w�� NULL
    //);
}

// �M�zDirect3D�MCOM
void CleanD3D()
{
    // ����������Ҧ���COM��H
    //Direct��l
    if (swapchain)
        swapchain->Release();
    if (dev)
        dev->Release();
    if (devcon)
        devcon->Release();
    //�w�İ�
    if (backbuffer)
        backbuffer->Release();
    //���I�H�ι����ۦ⾹
    if (pLayout)
        pLayout->Release();
    if (pVS)
        pVS->Release();
    if (pPS)
        pPS->Release();
    if (pVBuffer)
        pVBuffer->Release();
    if (depthStencilBuffer)
        depthStencilBuffer->Release();
    if (depthStencilState)
        depthStencilState->Release();

}

// �Ыحn��V�Ϊ�
void InitGraphics()
{
    // �ϥ� VERTEX ���c�إߤ@�ӤT����
    VERTEX OurVertices[] =
    {
        {0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
        {0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
        {-0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)}
    };


    //�إ߳��I�w�İ�
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;                  // CPU�MGPU���g�J�s���v��
    bd.ByteWidth = sizeof(VERTEX) * 3;               // size�OVERTEX���c���j�p* 3
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;         // �Χ@���I�w�İ�
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;      // ���\CPU�g�J�w�İ�

    dev->CreateBuffer(&bd, NULL, &pVBuffer);       // �إ߽w�İ�


    // �N���I�ƻs��w�İϤ�
    D3D11_MAPPED_SUBRESOURCE ms;
    devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // �M�g�w�İ�
    //memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // �ƻs�ƾ�
    devcon->Unmap(pVBuffer, NULL);                                      // �����M�g�w�İ�

    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
    depthStencilDesc.DepthEnable = TRUE;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    dev->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
    devcon->OMSetDepthStencilState(depthStencilState, 1);

}

// ���J�÷ǳƵۦ⾹
void InitPipeline()
{

    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
    depthStencilDesc.DepthEnable = TRUE;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    dev->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
    devcon->OMSetDepthStencilState(depthStencilState, 1);
    // ���J�ýsĶ��ӵۦ⾹
    ID3D10Blob* VS, * PS;
    D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
    D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

    // �N��ӵۦ⾹�ʸ˨�ۦ⾹����
    dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
    dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

    //�]�w�ۦ⾹��H
    devcon->VSSetShader(pVS, 0, 0);
    devcon->PSSetShader(pPS, 0, 0);

    // �إ߿�J�G����H
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
    devcon->IASetInputLayout(pLayout);
}


*/

//�H�W��DirectX 3D