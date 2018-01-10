#include <node.h>
#include <nan.h>
#include <dlfcn.h>
#include <cstdint>
#include <fyerwork.h>

using SetLocalServeAddressFcn = decltype(SetLocalServeAddress);
using SetCenterAddressFcn = decltype(SetCenterAddress);
using SetPortFcn = decltype(SetPort);
using SetMaxSendRecvMessageSizeFcn = decltype(SetMaxSendRecvMessageSize);
using SetClientPortFcn = decltype(SetClientPort);

using RegisterFileFcn = decltype(RegisterFile);
using UnregisterFileFcn = decltype(UnregisterFile);

using StartFyerworkServerFcn = decltype(StartFyerworkServer);
using StartFyerworkServerInBackgroundFcn = decltype(StartFyerworkServerInBackground);
using WaitFyerworkServerFcn = decltype(WaitFyerworkServer);

using FilesFcn = decltype(Files);
using FileInfoFcn = decltype(FileInfo);

using UploadFileFcn = decltype(UploadFile);
using DownloadFileFcn = decltype(DownloadFile);

SetLocalServeAddressFcn *set_local_serve_address;
SetCenterAddressFcn *set_center_address;
SetPortFcn *set_port;
SetMaxSendRecvMessageSizeFcn *set_max_send_recv_message_size;
SetClientPortFcn *set_client_port;

RegisterFileFcn *register_file;
UnregisterFileFcn *unregister_file;

StartFyerworkServerFcn *start_fyerwork_server;
StartFyerworkServerInBackgroundFcn *start_fyerwork_server_in_background;
WaitFyerworkServerFcn *wait_fyerwork_server;

FilesFcn *files_fcn;
FileInfoFcn *file_info_fcn;

UploadFileFcn *upload_file;
DownloadFileFcn *download_file;

void *handle;

NAN_METHOD(loadLib)
{
    if (info.Length() != 1)
        Nan::ThrowTypeError("loadLib requires exact one parameter");
    if (!info[0]->IsString())
        Nan::ThrowTypeError("loadLib requires a string parameter");

    char *lib_path = *Nan::Utf8String(info[0]);
    handle = dlopen(lib_path, RTLD_NOW);

    set_local_serve_address = (SetLocalServeAddressFcn *)dlsym(handle, "SetLocalServeAddress");
    set_center_address = (SetCenterAddressFcn *)dlsym(handle, "SetCenterAddress");
    set_max_send_recv_message_size = (SetMaxSendRecvMessageSizeFcn *)dlsym(handle, "SetMaxSendRecvMessageSize");
    set_port = (SetPortFcn *)dlsym(handle, "SetPort");
    set_client_port = (SetClientPortFcn *)dlsym(handle, "SetClientPort");

    register_file = (RegisterFileFcn *)dlsym(handle, "RegisterFile");
    unregister_file = (UnregisterFileFcn *)dlsym(handle, "UnregisterFile");

    start_fyerwork_server = (StartFyerworkServerFcn *)dlsym(handle, "SetFyerworkServer");
    start_fyerwork_server_in_background = (StartFyerworkServerInBackgroundFcn *)dlsym(handle, "StartFyerworkServerInBackground");
    wait_fyerwork_server = (WaitFyerworkServerFcn *)dlsym(handle, "WaitFyerworkServer");

    files_fcn = (FilesFcn *)dlsym(handle, "Files");
    file_info_fcn = (FileInfoFcn *)dlsym(handle, "FileInfo");

    upload_file = (UploadFileFcn *)dlsym(handle, "UploadFile");
    download_file = (DownloadFileFcn *)dlsym(handle, "DownloadFile");
}

NAN_METHOD(releaseLib)
{
    dlclose(handle);
}

NAN_METHOD(setLocalServeAddress)
{
    if (info.Length() != 1)
        Nan::ThrowTypeError("setLocalServeAddress requires exact one parameter");
    if (!info[0]->IsString())
        Nan::ThrowTypeError("setLocalServeAddress requires a string parameter");

    char *local_serve_address = *Nan::Utf8String(info[0]);
    set_local_serve_address(local_serve_address);
}

NAN_METHOD(setCenterAddress)
{
    if (info.Length() != 1)
        Nan::ThrowTypeError("setCenterAddress requires exact one parameter");
    if (!info[0]->IsString())
        Nan::ThrowTypeError("setCenterAddress requires a string parameter");

    char *center_address = *Nan::Utf8String(info[0]);
    set_center_address(center_address);
}

NAN_METHOD(setMaxSendRecvMessageSize)
{
    if (info.Length() != 1)
        Nan::ThrowTypeError("setMaxSendRecvMessageSize requires exact one parameter");
    if (!info[0]->IsNumber())
        Nan::ThrowTypeError("setMaxSendRecvMessageSize requires a number parameter");

    int max_send_recv_msg_size = static_cast<int>(Nan::To<int64_t>(info[0]).FromJust());
    set_max_send_recv_message_size(max_send_recv_msg_size);
}

NAN_METHOD(setPort)
{
    if (info.Length() != 1)
        Nan::ThrowTypeError("setPort requires exact one parameter");
    if (!info[0]->IsNumber())
        Nan::ThrowTypeError("setPort requires a number parameter");

    int port = static_cast<int>(Nan::To<uint32_t>(info[0]).FromJust());
    set_port(port);
}

NAN_METHOD(setClientPort)
{
    if (info.Length() != 1)
        Nan::ThrowTypeError("setClientPort requires exact one parameter");
    if (!info[0]->IsNumber())
        Nan::ThrowTypeError("setClientPort requires a number parameter");

    int client_port = static_cast<int>(Nan::To<uint32_t>(info[0]).FromJust());
    set_client_port(client_port);
}

NAN_METHOD(registerFile)
{
    if (info.Length() != 1)
        Nan::ThrowTypeError("registerFile requires exact one parameter");
    if (!info[0]->IsNumber())
        Nan::ThrowTypeError("registerFile requires a string parameter");

    char *file_path = *Nan::Utf8String(info[0]);
    if (register_file(file_path) != 0)
        Nan::ThrowError("failed to register file");
}

NAN_METHOD(unregisterFile)
{
    if (info.Length() != 1)
        Nan::ThrowTypeError("unregisterFile requires exact one parameter");
    if (!info[0]->IsNumber())
        Nan::ThrowTypeError("unregisterFile requires a string parameter");

    char *file_name = *Nan::Utf8String(info[0]);
    if (unregister_file(file_name) != 0)
        Nan::ThrowError("failed to unregister file");
}

NAN_METHOD(startFyerworkServerInBackground)
{
    start_fyerwork_server_in_background();
}

NAN_METHOD(fetchFileInfos)
{
    v8::Local<v8::Object> file_infos = Nan::New<v8::Object>();

    char **file_names;
    int file_num;
    if (files_fcn(&file_names, &file_num) != 0)
        Nan::ThrowError("failed to get file names");

    for (int i = 0; i < file_num; i++)
    {
        file_info fi;
        if (file_info_fcn(file_names[i], &fi) != 0)
            Nan::ThrowError("failed to fetch file info");
        v8::Local<v8::Object> finfo = Nan::New<v8::Object>();
        finfo->Set(Nan::New("size").ToLocalChecked(), Nan::New<v8::Number>(fi.size));
        finfo->Set(Nan::New("hash").ToLocalChecked(), Nan::CopyBuffer(reinterpret_cast<char *>(fi.hash), 16).ToLocalChecked());
        finfo->Set(Nan::New("fragCount").ToLocalChecked(), Nan::New<v8::Number>(fi.frag_count));
        finfo->Set(Nan::New("uploadTime").ToLocalChecked(), Nan::New<v8::Number>(fi.upload_time));
        file_infos->Set(Nan::New(file_names[i]).ToLocalChecked(), finfo);

        free(file_names[i]);
    }

    free(file_names);
    info.GetReturnValue().Set(file_infos);
}

NAN_METHOD(uploadFile)
{
    if (info.Length() != 3)
        Nan::ThrowTypeError("uploadFile requires exact three parameter");
    if (!info[0]->IsNumber())
        Nan::ThrowTypeError("uploadFile requires a string, a number and a bytes buffer parameters");

    char *file_name = *Nan::Utf8String(info[0]);
    uint64_t size = static_cast<uint64_t>(Nan::To<int64_t>(info[1]).FromJust());
    unsigned char *hash = reinterpret_cast<unsigned char *>(node::Buffer::Data(info[2]->ToObject()));
    size_t hash_len = node::Buffer::Length(info[2]->ToObject());
    if (upload_file(file_name, size, hash, hash_len) != 0)
        Nan::ThrowError("failed to upload file");
}

NAN_METHOD(downloadFile)
{
    if (info.Length() != 2)
        Nan::ThrowTypeError("downloadFile requires exact two parameter");
    if (!info[0]->IsNumber())
        Nan::ThrowTypeError("downloadFile requires two bytes buffer parameters");

    char *file_name = *Nan::Utf8String(info[0]), *store_path = *Nan::Utf8String(info[1]);
    if (download_file(file_name, store_path) != 0)
        Nan::ThrowError("failed to download file");
}

NAN_MODULE_INIT(Init)
{
    NAN_EXPORT(target, loadLib);
    NAN_EXPORT(target, releaseLib);

    NAN_EXPORT(target, setLocalServeAddress);
    NAN_EXPORT(target, setCenterAddress);
    NAN_EXPORT(target, setMaxSendRecvMessageSize);
    NAN_EXPORT(target, setPort);
    NAN_EXPORT(target, setClientPort);

    NAN_EXPORT(target, registerFile);
    NAN_EXPORT(target, unregisterFile);

    NAN_EXPORT(target, startFyerworkServerInBackground);

    NAN_EXPORT(target, fetchFileInfos);

    NAN_EXPORT(target, uploadFile);
    NAN_EXPORT(target, downloadFile);
}

NODE_MODULE(fyerwork, Init)
