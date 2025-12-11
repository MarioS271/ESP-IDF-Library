# FlexStruct

A type used to dynamically store thread-safe values identified by string keys.
It has integrated mutex handling, making it safe to work with FreeRTOS tasks.

### Implements:
* `FlexStruct` - Stores a dynamic set of values of varying type