# Yacht Dice개발

MFC, socket통신을 이용한 2인 보드 게임 개발

![image](https://github.com/homekepa/Yacht_Dice/assets/91517560/c6090f09-8f2e-4d8c-a18b-94134665584f)

TCP 통신을 이용한 멀티 쓰레드 방식으로 하나의 Server에 2명의 플레이어(Client)들이 연결되면 게임이 시작됩니다.
게임은 각 플레이어가 12라운드 동안 주사위를 굴려 점수판에 적힌 주사위 조합을 맞추어 높은 점수를 만드는 것을 목표로 하는 게임입니다.


![image](https://github.com/homekepa/Yacht_Dice/assets/91517560/a58aa8e6-337e-47f3-a6cc-ac176384f849)

위의 동작에서 채팅과 게임 데이터는 동시동작을 가능하기에 멀티쓰레딩을 통해 동시 동작 수행한다.

---
![image](https://github.com/homekepa/Yacht_Dice/assets/91517560/8c746cc3-987a-46fd-9a72-54bdf3dbf8db)

## 서버
![image](https://github.com/homekepa/Yacht_Dice/assets/91517560/7eb11c5d-c3e1-408e-8d3e-0c15b244e9f7)

양 클라이언트 측에서 전송받은 채팅 데이터, 게임 데이터를 계산하여 각 클라이언트에게 계산된 데이터를 보내준다.
<br>
서버측에서는 게임상황, 채팅 로그를 확인 할 수 있다.

## 클라이언트
![image](https://github.com/homekepa/Yacht_Dice/assets/91517560/50a04f92-d396-49e4-a484-132dd44729fb)

두명의 라이언트가 접속시 게임을 시작한다

![image](https://github.com/homekepa/Yacht_Dice/assets/91517560/e7b6d68c-969d-4e03-8512-3bb801bc0391)

게임이 무한이 진행되는 것을 방지하고자 제한 시간을 두어 턴이 강제로 종료되도록 하였습니다.<br>
Progress bar를 이용해 전체 시간의 비율을 주고, 10초정도 부터 남은 시간을 로그로 알려줍니다.

![image](https://github.com/homekepa/Yacht_Dice/assets/91517560/b92a58e0-aa44-46b5-bcdf-db671c071bca)

주사위 굴리기 버튼을 눌러 랜던함 1~6의 숫자를 뽑습니다. 그리고 주사위 값을 서버로 전송하여 서버에서 계산을 진행하여 각 클라이언트에게 게임 상황을 전달합니다.
<br> 
주사위는 본인 차례에 최대 3번 던질 수 있습니다.

![image](https://github.com/homekepa/Yacht_Dice/assets/91517560/6b1e91f8-011e-43d1-8215-d49707b3cdd6)

Lock을 통해 원하는 주사위를 굴리지 않을지 결정할 수 있습니다. (단 초기값은 0으로 Lock시 0으로 고정됩니다.)

![image](https://github.com/homekepa/Yacht_Dice/assets/91517560/29be0d92-b6cd-4c3f-89b9-e9876b562049)

상대 차례로 넘기기위해서는 무조건 자신의 표를 채워야합니다. 그러므로 삽입 버튼을 통해 표에 나온 수를 입력합니다.<br>
버튼을 통해 삽입 후 버튼은 비활성화되고 상대 차례로 넘어갑니다.<br>
본인의 차례가 아닌 경우 채팅을 제외한 데이터는 서버로 전송되지 않고 입력 또한 받지 않습니다.

![image](https://github.com/homekepa/Yacht_Dice/assets/91517560/775fa469-97e0-4f62-baea-f455fe437849)

---
### 참고자료 출처
https://zadd.tistory.com/33 //멀티스레드 사용
<br>
https://blog.naver.com/PostView.naver?blogId=skyvvv624&logNo=221509624084&redirect=Dlog&widgetTypeCall=true&directAccess=false // 스레드 생성방법
<br>
https://m.blog.naver.com/shoutjoy/221788478799 //멀티스레드 관련 함수 사용법
<br> 
https://kyungthe.tistory.com/26 // edit 박스 엔터키 사용
<br>
https://m.blog.naver.com/PostView.naver?blogId=klp0712&logNo=220616000963&categoryNo=18&proxyReferer= //프로그래스바를 이용한 타이머 카운트
