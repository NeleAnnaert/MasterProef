LIBDIR =../lib
CXXFLAGS += -I$(LIBDIR)

all: test_pro test TestOpslaan testOphalen testMasker testDetBed testMov testCam testMovN testAutBed saveBed programma

test_pro: test_pro.o $(LIBDIR)/$(LIBSEEK)
test: test.o $(LIBDIR)/$(LIBSEEK)
TestOpslaan: TestOpslaan.o $(LIBDIR)/$(LIBSEEK) 
testOphalen: testOphalen.o $(LIBDIR)/$(LIBSEEK)
testMasker: testMasker.o $(LIBDIR)/$(LIBSEEK)
testBed: testBed.o $(LIBDIR)/$(LIBSEEK)
testDetBed: testDetBed.o $(LIBDIR)/$(LIBSEEK)
testMov: testMov.o $(LIBDIR)/$(LIBSEEK)
testCam: testCam.o $(LIBDIR)/$(LIBSEEK)
testMovN: testMovN.o $(LIBDIR)/$(LIBSEEK)
testAutBed: testAutBed.o $(LIBDIR)/$(LIBSEEK)
saveBed: saveBed.o $(LIBDIR)/$(LIBSEEK)
programma: programma.o $(LIBDIR)/$(LIBSEEK)

clean:
	rm -rf test_pro test *.o TestOpslaan.o testOphalen.o testMasker.o testBed.o testDetBed.o testMov.o testCam.o testMovN.o testAutBed.o saveBed.o programma

.PHONY: clean all

