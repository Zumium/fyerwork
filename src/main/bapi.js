import { ipcMain } from 'electron';
import { basename } from 'path';
import { statSync } from 'fs';
import { sync as md5Sync } from 'md5-file';
import { fetchFileInfos, registerFile, uploadFile, downloadFile } from './fw';

ipcMain.on('fetch-file-infos', event => {
    event.returnValue = fetchFileInfos();
});

ipcMain.on('upload-file', (event, filepath) => {
    try {
        registerFile(filepath);
        let stat = statSync(filepath);
        let hash = new Buffer(md5Sync(filepath), 'hex');
        uploadFile(basename(filepath), stat.size, hash);
    }
    catch (e) {
        event.returnValue = e;
    }
});

ipcMain.on('download-file', (event, name, storePath) => {
    try {
        downloadFile(name, process.env.FYERWORK_DOWNLOAD_DIR);
        event.sender.send('download-file-complete', name);
    } catch (e) {
        event.sender.send('download-file-fail', e.message);
    }
});