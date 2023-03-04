import { createRouter, createWebHashHistory } from "vue-router";

// 页面路由导入
import homePage from "../src/components/homePage.vue"
import about from "../src/components/about.vue"
import clusterAlgorithm from "../src/components/clusterAlgorithm.vue"
import linearSort from "../src/components/linearSort.vue"
import neuralNetwork from "../src/components/neuralNetwork.vue"
import maskDetect from "../src/components/maskDetect.vue"


const router = createRouter({
    history:createWebHashHistory(),
    // 引入路由
    routes:[
        {
            path:'/',
            component:homePage
        },
        {
            path:'/about',
            component:about
        },
        {
            path:'/clusterAlgorithm',
            component:clusterAlgorithm
        },
        {
            path:'/linearSort',
            component:linearSort
        },
        {
            path:'/neuralNetwork',
            component:neuralNetwork
        },
        {
            path:'/maskDetect',
            component:maskDetect
        }
    ]
});


export default router


