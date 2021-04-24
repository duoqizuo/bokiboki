---
# BOKIBOKI
-------------

> 关于我们，欢迎关注  

项目是基于ue4，蓝图和C++混合开发的

### 代码布局

─bokiboki
    │  GetStarted.Target.cs																							
    │  GetStartedEditor.Target.cs
    │
    └─GetStarted															//启动项
        │  GetStarted.Build.cs
        │  GetStarted.cpp
        │  GetStarted.h
        │  GetStartedGameModeBase.cpp
        │  GetStartedGameModeBase.h
        │
        ├─Characters														//角色
        │  ├─Enemys 														//敌人
        │  │      Enemy.cpp
        │  │      Enemy.h
        │  │      EnemyAnimInstance.cpp
        │  │      EnemyAnimInstance.h
        │  │
        │  └─Player 															//玩家
        │          ZhuJue_AnimInstance.cpp
        │          ZhuJue_AnimInstance.h
        │          ZhuJue_Character.cpp
        │          ZhuJue_Character.h
        │
        ├─GameMode 													//关卡模式
        │      Level1_GameMode.cpp
        │      Level1_GameMode.h
        │
        └─GamePlay 													//游戏组件
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

### TODO（可选）

接下来的开发/维护计划。