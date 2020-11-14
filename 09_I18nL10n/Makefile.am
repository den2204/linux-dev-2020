bin_PROGRAMS=binarysearch
binarysearch_SOURCES=main.c
pkgdata_DATA=ru/LC_MESSAGES/binarysearch.mo

create_pot: main.c
	xgettext -k_ -c main.c -o binarysearch.pot

binarysearch.pot:	main.c
	xgettext -k_ -c main.c -o tmp.pot
	msgmerge -U binarysearch.pot tmp.pot
	rm tmp.pot


init:	binarysearch.pot
	msginit -i binarysearch.pot -o binarysearch_ru.po -l ru


binarysearch_ru.po:	binarysearch.pot
	msgmerge -U $@ $<


ru/LC_MESSAGES/binarysearch.mo: binarysearch_ru.po
	mkdir -p ru/LC_MESSAGES
	msgfmt binarysearch_ru -o $@




