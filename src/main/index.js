import { app, BrowserWindow } from 'electron'
import { join } from 'path';
import { loadLib, releaseLib, setCenterAddress, setLocalServeAddress, startFyerworkServerInBackground } from './fw';
import './bapi';

/**
 * Set `__static` path to static files in production
 * https://simulatedgreg.gitbooks.io/electron-vue/content/en/using-static-assets.html
 */
if (process.env.NODE_ENV !== 'development') {
  global.__static = require('path').join(__dirname, '/static').replace(/\\/g, '\\\\')
}

let mainWindow;
const winURL = process.env.NODE_ENV === 'development' ?
  `http://localhost:9080` :
  `file://${__dirname}/index.html`;

function createWindow() {
  /**
   * Initial window options
   */
  mainWindow = new BrowserWindow({
    height: 563,
    useContentSize: true,
    width: 1000,
    autoHideMenuBar: true
  });

  mainWindow.loadURL(winURL);

  mainWindow.on('closed', () => {
    mainWindow = null
  })
}

app.on('ready', createWindow);
app.on('ready', () => {
  loadLib(join(__dirname, '..', '..', 'lib', 'fyerwork.so'));
  setCenterAddress(process.env.FYERWORK_CENTER_ADDRESS);
  setLocalServeAddress(process.env.FYERWORK_LOCAL_ADDRESS);
  startFyerworkServerInBackground();
});

app.on('will-quit', releaseLib);

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
});

app.on('activate', () => {
  if (mainWindow === null) {
    createWindow()
  }
});
