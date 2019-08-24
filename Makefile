.PHONY: clean All

All:
	@echo "----------Building project:[ ntp - Release ]----------"
	@cd "ntp" && "$(MAKE)" -f  "ntp.mk"
clean:
	@echo "----------Cleaning project:[ ntp - Release ]----------"
	@cd "ntp" && "$(MAKE)" -f  "ntp.mk" clean
