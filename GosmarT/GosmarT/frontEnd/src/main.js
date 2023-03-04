import { createApp } from 'vue'
import App from './App.vue'
import './index.css'

// 包引入
import router from '../router/index.js'
import ElementPlus from 'element-plus'  
import "element-plus/dist/index.css"
import * as ElementPlusIconsVue from '@element-plus/icons-vue'

const app = createApp(App)


app.use(ElementPlus)                                                    // element-plus 引入
app.use(router);                                                        // router 引入
for (const [key, component] of Object.entries(ElementPlusIconsVue)) {   // icon 引入
    app.component(key, component)
}

app.mount('#app');
