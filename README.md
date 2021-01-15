# Indoor Air Quality Detection and AIoT Application  : 室內空氣品質偵測與人工智慧物聯網應用 
**Huafan University Department of Electronic Engineering MA Hui-En Lin**
以下是論文口試報告時的少部分內容

## 摘要
  本研究旨在以 AIOT結合APP檢視室內辦公空間的空氣品質。目前市面上較少檢測室內CO2濃度的小型產品，所以此研究利用**LinkIt7697**開發出一款適合室內空間使用的空氣品質偵測產品，以及配合現在興盛的外送平台使用**Raspberry Pi4**進行AI物體辨識，減少外送到達時，找不到客戶的窘境。
  
  **外觀架構圖:**
![image](https://github.com/FeenLin/Master_of_Science_thesis/blob/master/Picture/1.png)

## 研究動機
近年來隨著全球暖化及氣象異常的情況逐日增長人們開始注重生活環境，而在生活環境中空氣品質一直是人們所特別關注的問題，尤其是霧霾、PM2.5等名詞出現在新聞的氣象預報中，但是這些都是注重於室外空間在大範圍環境的偵測數值，並不適用於在日常室內小型空間，例如：小規模辦公室、學校實驗室等。在外送盛行的時代，常常會出現外送人員送來，櫃台等接待人員會去做確認再詢問公司同仁是否有訂外送，而有快遞來收送貨時一樣需要有人去接應再詢問，這樣的來來回回會增加櫃台的工作量並浪費工作的時間，而部分小型辦公室是沒有櫃台的，會照成更大的麻煩，所以櫃台前有辨識系統就能減少些不必要的人事成本支出。


## 論文架構圖
  **硬體 & MCS& APP流程圖:**

![image](https://github.com/FeenLin/Master_of_Science_thesis/blob/master/Picture/2.png)

  **AI 物體辨識流程圖:**

![image](https://github.com/FeenLin/Master_of_Science_thesis/blob/master/Picture/3.png)



## 軟體配置Middleware、 Presentation與AI應用
使用APP Inventer製作手機APP程式，擁有登入、註冊與主要介面，登入與註冊是連接Google firebase連動，主要介面顯示從MCS上撈取的感測器數值並顯示出來，以及配有一組加濕器開關可以透過UDP通訊控制硬體端。
![image]()

AI應用是使用 Google Teachable Machine製作Model和Label，參考文獻[1]的教學文章並修改成適合的.py檔套入樹莓派使用，透過USB攝影機辨識Uber Eat、Foodpanda與Packages。
![image]()

## 研究實品
![image](https://github.com/FeenLin/Master_of_Science_thesis/blob/master/Picture/final.png)
## 參考資料
[1]	許钰莨，曾俊霖。使用Google Teachable Machine 來實現Raspberry Pi 4 的影像分類推論。Designspark，2020年09月03日，取自https://www.rs-online.com/designspark/google-teachable-machine-raspberry-pi-4-cn

