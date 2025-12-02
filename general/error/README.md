# Error

Custom ESP_ERROR_CHECK-style error checker implementation making use of my custom logging system.

### Implements:
* ERROR_CHECK(tag, x)  -  Error Checks, incase of failiure: logs error and halts execution
* WARN_CHECK(tag, x)  -  Error Checks, incase of failiure: logs warning

### Depends on:
* logger.h
