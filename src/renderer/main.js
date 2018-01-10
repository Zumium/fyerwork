import Vue from 'vue'

import App from './App'
import router from './router'
import ElementUI from 'element-ui'
import 'element-ui/lib/theme-chalk/index.css'
import Resource from 'vue-resource'

if (!process.env.IS_WEB) Vue.use(require('vue-electron'))
Vue.config.productionTip = false

/* eslint-disable no-new */
Vue.use(ElementUI);
Vue.use(Resource);
// Zumium 配置要调用的后端端口
// Vue.http.options.root = 'http://localhost:8007'

new Vue({
  components: { App },
  router,
  template: '<App/>'
}).$mount('#app')
