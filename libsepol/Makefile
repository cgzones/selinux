DISABLE_CIL ?= n

export DISABLE_CIL

all: 
	$(MAKE) -C src 
	$(MAKE) -C utils
	$(MAKE) -C checkpolicy

install: 
	$(MAKE) -C include install
	$(MAKE) -C src install
	$(MAKE) -C utils install
	$(MAKE) -C man install
	$(MAKE) -C checkpolicy install

relabel:
	$(MAKE) -C src relabel
	$(MAKE) -C checkpolicy relabel

clean:
	$(MAKE) -C src clean
	$(MAKE) -C utils clean
	$(MAKE) -C checkpolicy clean
	$(MAKE) -C tests clean

indent:
	$(MAKE) -C src $@
	$(MAKE) -C include $@
	$(MAKE) -C utils $@
	$(MAKE) -C checkpolicy $@

test:
	$(MAKE) -C tests test
	$(MAKE) -C checkpolicy test
