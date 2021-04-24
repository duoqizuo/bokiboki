---
# BOKIBOKI
-------------

> 关于我们，欢迎关注  

项目是基于ue4，蓝图和C++混合开发的

### 代码布局

```c++
─bokiboki
    │  GetStarted.Target.cs																							
    │  GetStartedEditor.Target.cs
    └─GetStarted			//启动项
        │  GetStarted.Build.cs
        │  GetStarted.cpp
        │  GetStarted.h
        │  GetStartedGameModeBase.cpp
        │  GetStartedGameModeBase.h
        │
        ├─Characters		//角色
        │  ├─Enemys 		//敌人
        │  │      Enemy.cpp
        │  │      Enemy.h
        │  │      EnemyAnimInstance.cpp
        │  │      EnemyAnimInstance.h
        │  │
        │  └─Player 	    //玩家
        │          ZhuJue_AnimInstance.cpp
        │          ZhuJue_AnimInstance.h
        │          ZhuJue_Character.cpp
        │          ZhuJue_Character.h
        │
        ├─GameMode 			//关卡模式
        │      Level1_GameMode.cpp
        │      Level1_GameMode.h
        │
        └─GamePlay 			//游戏组件
                BaoZhaWu.cpp
                BaoZhaWu.h
                FuDongPingTai.cpp
                FuDongPingTai.h
                JiaoHuXiTong.cpp
                JiaoHuXiTong.h
                JiGuanMen_Actor.cpp
                JiGuanMen_Actor.h
                ShengChengSpace.cpp
                ShengChengSpace.h
                ShiQuWu.cpp
                ShiQuWu.h
                Weapon_Actor.cpp
                Weapon_Actor.h
```

### TODO（可选）

接下来的开发/维护计划。



.bokiboki
├── mmPlayer                                        // 项目打包版本，可直接使用
├── public                                          // 静态资源目录
│   └─index.html                                    // 入口html文件
├── screenshots                                     // 项目截图
├── src                                             // 项目源码目录
│   ├── api                                         // 数据交互目录
│   │   └── index.js                                // 获取数据
│   ├── assets                                      // 资源目录
│   │   ├── css                                     // 样式文件目录
│   │   │   ├── index.less                          // mmPlayer相关基础样式
│   │   │   ├── mixin.less                          // 样式混合
│   │   │   ├── reset.less                          // 样式重置
│   │   │   └── var.less                            // 样式变量（字体大小、字体颜色、背景颜色）
│   │   ├── img                                     // 静态图片目录
│   │   └── js                                      // 数据交互目录
│   │        ├── hack.js                            // 修改 nextTick 
│   │        ├── mixin.js                           // 组件混合
│   │        ├── song.js                            // 数据处理
│   │        ├── storage.js                         // localstorage配置
│   │        └── util.js                            // 公用js方法
│   ├── base                                        // 公共基础组件目录
│   │   ├── mm-dialog
│   │   │   └── mm-dialog.vue                       // 对话框组件
│   │   ├── mm-loading
│   │   │   └── mm-loading.vue                      // 加载动画组件
│   │   ├── mm-no-result
│   │   │   └── mm-no-result.vue                    // 暂无数据提示组件
│   │   ├── mm-progress
│   │   │   └── mm-progress.vue                     // 进度条拖动组件
│   │   └── mm-toast
│   │        ├── index.js                           // mm-toast 组件插件化配置
│   │        └── mm-toast.vue                       // 弹出层提示组件
│   ├── components                                  // 公共项目组件目录
│   │   ├── lyric
│   │   │   └── lyric                               // 歌词和封面组件
│   │   └── mm-header
│   │   │   └── mm-header.vue                       // 头部组件
│   │   ├── music-btn
│   │   │   └── music-btn.vue                       // 按钮组件
│   │   └── music-list
│   │        └── music-list.vue                     // 列表组件
│   ├── pages                                       // 入口主文件
│   │   ├── comment
│   │   │   └── comment.vue                         // 评论
│   │   ├── details
│   │   │   └── details.vue                         // 排行榜详情
│   │   ├── historyList
│   │   │   └── historyList.vue                     // 我听过的（播放历史）
│   │   ├── playList
│   │   │   └── playList.vue                        // 正在播放
│   │   ├── search
│   │   │   └── search.vue                          // 搜索
│   │   ├── topList
│   │   │   └── topList.vue                         // 排行榜页面
│   │   ├── userList
│   │   │   └── userList.vue                        // 我的歌单
│   │   ├── mmPlayer.js                             // 播放器事相关件绑定
│   │   └── music.vue                               // 播放器主页面
│   ├── router
│   │   └── index.js                                // 路由配置
│   ├── store                                       // vuex的状态管理
│   │   ├── actions.js                              // 配置actions
│   │   ├── getters.js                              // 配置getters
│   │   ├── index.js                                // 引用vuex，创建store
│   │   ├── mutation-types.js                       // 定义常量mutations名
│   │   ├── mutations.js                            // 配置mutations
│   │   └── state.js                                // 配置state
│   ├── App.vue                                     // 根组件
│   ├── config.js                                   // 基本配置
│   └── main.js                                     // 入口主文件
└── vue.config.js                                   // vue-cli 配置文件
</code></pre>
</code></pre>