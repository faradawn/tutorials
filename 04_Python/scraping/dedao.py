import requests

class Dedao:
  def __init__(self):
    self.base_url = 'https://entree.igetget.com/acropolis/v1/audio/listall'
    self.max_id = 0
    self.headers = {
      'Host': 'entree.igetget.com',
      'X-OS': 'iOS',
      'X-NET': 'wifi',
      'Accept': '*/*',
      'X-Nonce': '779b79d1d51d43fa',
      'Accept-Encoding': 'br, gzip, deflate',
      #     'Content-Length': '    67',
      'X-TARGET': 'main',
      'User-Agent': '%E5%BE%97%E5%88%B0/4.0.13 CFNetwork/901.1 Darwin/17.6.0',
      'X-CHIL': 'appstore',
      'Cookie    ': 'acw_tc=AQAAAC0YfiuHegUAxkvoZRLraUMQyRfH; aliyungf_tc=AQAAAKwCD1dINAUAxkvoZTppW+jezS/9',
      'X-UID': '34556154',
      'X-AV    ': '4.0.0',
      'X-SEID    ': '',
      'X-SCR    ': '1242*2208',
      'X-DT': 'phone',
      'X-S': '91a46b7a31ffc7a2',
      'X-Sign': 'ZTBiZjQyNTI1OTU2MTgwZjYwMWRhMjc5ZjhmMGRlNGI=',
      'Accept-Language': 'zh-cn',
      'X-D': 'ca3c83fca6e84a2d869f95829964ebb8',
      'X-THUMB': 'l',
      'X-T': 'json',
      'X-Timestamp': '1528195376',
      'X-TS': '1528195376',
      'X-U': '34556154',
      'X-App-Key': 'ios-4.0.0',
      'X-OV': '11.4',
      'Connection': 'keep-alive',
      'X-ADV': '1',
      'Content-Type': 'application/x-www-form-urlencoded',
      'X-V': '2',
      'X-IS_JAILBREAK    ': 'NO',
      'X-DV': 'iPhone10,2',
    }

  def request_data(self):
    try:
      data = {
          'max_id': self.max_id,
          'since_id': 0,
          'column_id': 2,
          'count': 20,
          'order': 1,
          'section': 0
      }
      response = requests.post(self.base_url, headers=self.headers, data=data)
      print('yay', response)
    except Exception as e:
      print('no', e)
      time.sleep(2)
      pass

d = Dedao()
d.request_data()