import * as bindings from 'bindings';
const fw = bindings('fyerwork');

export const loadLib = fw.loadLib;
export const releaseLib = fw.releaseLib;

export const setLocalServeAddress = fw.setLocalServeAddress;
export const setCenterAddress = fw.setCenterAddress;
export const setMaxSendRecvMessageSize = fw.setMaxSendRecvMessageSize;
export const setPort = fw.setPort;
export const setClientPort = fw.setClientPort;

export const registerFile = fw.registerFile;
export const unregisterFile = fw.unregisterFile;

export const startFyerworkServerInBackground = fw.startFyerworkServerInBackground;

export const fetchFileInfos = fw.fetchFileInfos;

export const uploadFile = fw.uploadFile;
export const downloadFile = fw.downloadFile;