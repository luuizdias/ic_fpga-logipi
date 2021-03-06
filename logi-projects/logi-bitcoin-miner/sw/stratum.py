# Echo server program
import socket
import sys
import json
from hashlib import sha256
from binascii import hexlify, unhexlify

HOST = 'eu-stratum.btcguild.com'
PORT = 3333         

extranonce2_size = 4    

def chunks(l, n):
	for i in xrange(0, len(l), n):
		yield l[i:i+n]

def increment_nonce(nonce, size):
	next_nonce = long(nonce, 16) + 1
	if len('%x' % next_nonce) > (size * 2):
		return '00' * size
	return ('%0' + str(size * 2) +'x') % next_nonce

def getStratumResponse(stratum_s):
	msg = ''
	data = stratum_s.recv(1)
	while data != '\n':
		msg = msg + data
		data = stratum_s.recv(1)		
	return msg	

subscribe_request = {"id":1, "method":"mining.subscribe", "params": []}
worker_register = {"params": ["voelker_1", "1234"], "id": 1, "method": "mining.authorize"}

for res in socket.getaddrinfo(HOST, PORT, socket.AF_UNSPEC, socket.SOCK_STREAM):
	af, socktype, proto, canonname, sa = res
	try:
		s = socket.socket(af, socktype, proto)
	except socket.error, msg:
		s = None
		continue
	try:
		s.connect(sa)
	except socket.error, msg:
		s.close()
		s = None
		continue
	break
if s is None:
	print 'could not open socket'
	sys.exit(1)

s.send(json.dumps(subscribe_request)+'\n')
sub_resp = getStratumResponse(s)
print 'Received', repr(sub_resp)
resp_json = json.loads(sub_resp)
extranonce = resp_json['result'][1]
extranonce2_size = resp_json['result'][2]

s.send(json.dumps(worker_register)+'\n')
print 'Received', repr(getStratumResponse(s))
job = json.loads(getStratumResponse(s))
job_id = job['params'][0]
prevhash = job['params'][1]
coinb1 = job['params'][2]
coinb2 = job['params'][3]
merkle_branch = job['params'][4]
version = job['params'][5]
nbits = job['params'][6]
ntimes = job['params'][7]
extranonce2 = extranonce2_size * '00'
extranonce2 = increment_nonce(extranonce2, extranonce2_size)
coinbase = coinb1 + extranonce + extranonce2 + coinb2
merkle_root = sha256(sha256(unhexlify(coinbase)).digest()).digest()

for hash_ in merkle_branch:
	merkle_root = sha256(sha256(merkle_root + unhexlify(hash_)).digest()).digest()
merkle_root_reversed = ''
for word in chunks(merkle_root, 4):
	merkle_root_reversed += word[::-1]
merkle_root = hexlify(merkle_root_reversed)

print repr(merkle_root)
print repr(prevhash)
print len(merkle_root)*4+(len(prevhash)*4)

