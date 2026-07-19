1. BP_Treehold_UIbuilder
   - 保持している変数
   - widgetmaster ( WBP Mission Master UI )
   - widget ( WBP M Body UI ) 
2. ST_Testmission StartLogic
3. build UI
    - STT MainMission -> BP_Treehold_UIbuilder.widget
    - STT_BunkiMission -> BP_Treehold_UIbuilder.widget

build UIの時に進行度を読み込みたい？



- BP_Treehold_UIbuilder
    - 機能
    - ミッションの情報を保持 (ST_Testmission)
    - WBP_M_BodyUIの保持
    - StateTreeの起動

- ST_Testmission( StateTree )
    - 出力するか判定　 (まだ)
    - 葉っぱでミッション情報を出力
        - STT Main Mission
        - STT_BunkiMission