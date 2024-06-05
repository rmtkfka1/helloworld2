#include "pch.h"
#include "RootSignature.h"
#include "Core.h"
RootSignature::RootSignature()
{
}
RootSignature::~RootSignature()
{
}

void RootSignature::Init()
{
    // ���� ���÷� ����
    D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    samplerDesc.MipLODBias = 0;
    samplerDesc.MaxAnisotropy = 0;
    samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
    samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
    samplerDesc.MinLOD = 0.0f;
    samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
    samplerDesc.ShaderRegister = 0;
    samplerDesc.RegisterSpace = 0;
    samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    // ��ũ���� ���� ����
    D3D12_DESCRIPTOR_RANGE ranges[2] =
    {
        { D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 4, 1, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND }, // b1 ~ b4
        { D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 5, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND } //  t0 ~t4
    };

    // ��Ʈ �Ķ���� ����
    // ����32��Ʈ ��������� (Constants)         =>        SetGraphicsRoot32BitConstants / SetGraphicsRoot32BitConstant
    // ������ �ž��ٶ� ���  (Descriptor)        =>        SetGraphicsRootConstantBufferView /SetGraphicsRootShaderResourceView
    // ���̺� �̿��ҋ� ���  (DescriptorTable)   =>        SetDescriptorHeaps / SetGraphicsRootDescriptorTable

    D3D12_ROOT_PARAMETER rootParameters[3];

    //������� ���
    rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
    rootParameters[0].Descriptor.ShaderRegister = 0; //b0
    rootParameters[0].Descriptor.RegisterSpace = 0;
    rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
    

    //���̺� ���
    rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(ranges);
    rootParameters[1].DescriptorTable.pDescriptorRanges = ranges;
    rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;


    //������� ��� ( �ν��Ͻ� StructedBuffer �ž��ً� ����Ұ��� )
    rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV;
    rootParameters[2].Descriptor.ShaderRegister = 5;  //t5
    rootParameters[2].Descriptor.RegisterSpace = 0;
    rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    // ��Ʈ ���� ����
    D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
    rootSignatureDesc.NumParameters = _countof(rootParameters);
    rootSignatureDesc.pParameters = rootParameters;
    rootSignatureDesc.NumStaticSamplers = 1;
    rootSignatureDesc.pStaticSamplers = &samplerDesc;
    rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

  
    ComPtr<ID3DBlob> signature;
    ComPtr<ID3DBlob> error;
    D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
    core->GetDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&_rootSignature));
}
