SRC=./src/a.go
GO=~/go/bin/go1.12.16
GOPATH_=$(shell go env GOPATH)
GOFLAGS=-x
#GOFLAGS+=-ldflags '-w -s' 
BIN=./bin/a.out
MKDIR=mkdir
RM=rm
UPX=echo upx
all:compress
$(BIN):export GOPATH=$(GOPATH_)
#$(BIN):export GOARCH=arm64
#$(BIN):export GOOS=android
$(BIN):$(SRC)
	@-$(MKDIR) -p $(@D)
	$(GO) build $(GOFLAGS) -o $(BIN) $(SRC)
compress:$(BIN)
	@-$(UPX) $(BIN)
run:$(BIN)
	@-$(BIN)
.phony:clean
clean:
	$(RM) $(BIN)
