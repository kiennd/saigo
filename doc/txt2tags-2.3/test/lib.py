#
# txt2tags test-suite library (http://txt2tags.sf.net)
# See also: run.py, */run.py
#

import os, string, time

# default program call to all tests
TXT2TAGS = "txt2tags -q --no-rc"

CONFIG_FILE = 'config'
CSS_FILE = 'css'
DIR_OK = 'ok'
DIR_ERROR = 'error'

OK = FAILED = 0
ERROR_FILES = []

MSG_RUN_ALONE = "No No No. Call me with ../run.py\nI can't be runned alone."

#
# file tools
#
def ReadFile(filename):
	return open(filename, 'r').read()

def WriteFile(filename, content=''):
	f = open(filename, 'w')
	f.write(content)
	f.close()

def MoveFile(orig, target):
	if os.path.isfile(target): os.remove(target)
	os.link(orig, target)
	os.remove(orig)

#
# auxiliar tools
#
def initTest(name, infile, outfile):
		okfile  = os.path.join(DIR_OK, outfile)
		print '  Testing %s ...' % name,
		if not os.path.isfile(okfile):
			print 'Skipping test (missing %s)' % okfile
			return False
		return True

def getFileMtime(file):
	ret = "-NO-MTIME-"
	if os.path.isfile(file):
		ret = time.strftime('%Y%m%d',time.localtime(os.path.getmtime(file)))
	return ret

def getCurrentDate():
	return time.strftime('%Y%m%d',time.localtime(time.time()))

#
# the hot tools
#
def convert(options):
	if type(options) in [type(()), type([])]:
		options = string.join(options, ' ')
	cmdline = TXT2TAGS + ' ' + options
	#print "+ Executing:",cmdline
	os.system(cmdline)

def diff(file):
	global OK, FAILED, ERROR_FILES
	okfile = os.path.join(DIR_OK, file)
	out = ReadFile(file)
	ok = ReadFile(okfile)
	if out != ok:
		print 'FAILED'
		FAILED = FAILED + 1
		if not os.path.isdir(DIR_ERROR):
			os.mkdir(DIR_ERROR)
		MoveFile(file, os.path.join(DIR_ERROR, file))
		ERROR_FILES.append(file)
	else:
		print 'OK'
		OK = OK + 1
		os.remove(file)

