import requests, json

mail = ''
key = ''
headers = {}

zoneList = []
selectedZone = {}
zoneListUrl = 'https://api.cloudflare.com/client/v4/zones'
recordListUrl = 'https://api.cloudflare.com/client/v4/zones/{0}/dns_records?type=A'
IPUrl = 'https://getipv4.azurewebsites.net/'
recordUrl = 'https://api.cloudflare.com/client/v4/zones/{0}/dns_records'
updateUrl = 'https://api.cloudflare.com/client/v4/zones/{0}/dns_records/{1}'

def initVar():
  mail = raw_input("enter your mail:").strip()
  key = raw_input("enter your key:").strip()
  return (mail, key)

def initHeaders():
  return {'X-Auth-Email': mail, 'X-Auth-Key': key, 'Content-Type': 'application/json'}

def getZoneList():
  resp = requests.get(zoneListUrl, headers=headers)
  ret = json.loads(resp.text)
  ret = map(lambda item: {'id': item[u'id'].encode("ascii"), 'name': item[u'name'].encode("ascii")}, ret[u'result'])
  return ret

def getRecordList():
  resp = requests.get(recordListUrl.format(selectedZone['id']), headers=headers)
  ret = json.loads(resp.text)
  ret = map(lambda item: {'id': item[u'id'].encode("ascii"), 'name': item[u'name'].encode("ascii")}, ret[u'result'])
  return ret

def selectZone():
  print 'zone list'
  for index, item in enumerate(zoneList):
    print '[' + str(index)  + ']:' + item['name']
  selectedIndex = raw_input('select a zone:')
  return zoneList[int(selectedIndex)]

def getIP():
  return requests.get(IPUrl).text

def record():
  name = raw_input('enter record name:')
  if name != selectedZone['name']:
    name = name + '.' + selectedZone['name']
  recordList = getRecordList()
  hasRecord = False
  rid = None
  for item in recordList:
    if item['name'] == name:
      hasRecord = True
      rid = item['id']
      break
  ip = getIP()
  payload = json.dumps({'type': 'A', 'name': name, 'content': ip})
  resp = None
  if hasRecord:
    print 'Waiting for update record'
    resp = requests.put(updateUrl.format(selectedZone['id'], rid), headers=headers, data=payload)
  else:
    print 'Waiting for create record'
    resp = requests.post(recordUrl.format(selectedZone['id']), headers=headers, data=payload)
  resp = json.loads(resp.text)
  if resp[u'success']:
    print 'done'
  else:
    print 'error'
    print resp

mail,key = initVar()
headers = initHeaders()
zoneList = getZoneList()
selectedZone = selectZone()
record()
