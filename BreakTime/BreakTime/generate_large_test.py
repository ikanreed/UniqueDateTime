from random import randint
from datetime import datetime, timezone, timedelta


def main(argv):
    if len(argv)!=3:
        print('requires [count] and [outfile] arugments')
        exit()
    numdates=int(argv[1])
    with open(argv[2],'w') as outfile:
        for i in range(numdates):
            written=datetime(year=randint(1000,2025), month=randint(1,12), day=randint(1,28), hour=randint(0,23), minute=randint(0,59), second=randint(0,59), tzinfo=timezone(timedelta(hours=randint(-12,12))))
            outfile.write(str(written).replace(' ','T'))
            outfile.write('\n')


if __name__=="__main__":
    import sys
    main(sys.argv)