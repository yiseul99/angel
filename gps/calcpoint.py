#-coding:UTF-8-*-
import math 

def grid(v1, v2) :

	RE = 6371.00877 # 지구 반경(km) 
	GRID = 5.0 # 격자 간격(km) 
	SLAT1 = 30.0 # 투영 위도1(degree) 
	SLAT2 = 60.0 # 투영 위도2(degree) 
	OLON = 126.0 # 기준점 경도(degree) 
	OLAT = 38.0 # 기준점 위도(degree) 
	XO = 43 # 기준점 X좌표(GRID) 
	YO = 136 # 기1준점 Y좌표(GRID) 

	DEGRAD = math.pi / 180.0 
	RADDEG = 180.0 / math.pi 

	re = RE / GRID; 
	slat1 = SLAT1 * DEGRAD 
	slat2 = SLAT2 * DEGRAD 
	olon = OLON * DEGRAD 
	olat = OLAT * DEGRAD 
	sn = math.tan(math.pi * 0.25 + slat2 * 0.5) / math.tan(math.pi * 0.25 + slat1 * 0.5) 
	sn = math.log(math.cos(slat1) / math.cos(slat2)) / math.log(sn) 
	sf = math.tan(math.pi * 0.25 + slat1 * 0.5) 
	sf = math.pow(sf, sn) * math.cos(slat1) / sn 
	ro = math.tan(math.pi * 0.25 + olat * 0.5) 
	ro = re * sf / math.pow(ro, sn); 
	rs = {}; 

	ra = math.tan(math.pi * 0.25 + (v1) * DEGRAD * 0.5)
	ra = re * sf / math.pow(ra, sn) 

	theta = v2 * DEGRAD - olon 
	if theta > math.pi : 
		theta -= 2.0 * math.pi 
	if theta < -math.pi : 
		theta += 2.0 * math.pi 

	theta *= sn 
	rs['x'] = (ra * math.sin(theta) + XO + 0.5) 
	rs['y'] = (ro - ra * math.cos(theta) + YO + 0.5) 

	string = "http://www.kma.go.kr/wid/queryDFS.jsp?gridx={0}&gridy={1}".format(
	str(rs["x"]).split('.')[0], str(rs["y"]).split('.')[0]) 
	return string 

if __name__ == "__main__" : 
	print (grid(37.566826005485716, 126.9786567859313))
