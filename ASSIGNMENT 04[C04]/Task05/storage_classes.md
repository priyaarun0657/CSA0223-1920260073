# Storage Classes
- auto: block scope, automatic lifetime, typically uninitialized indeterminate value.
- static local: block scope, entire program lifetime, initialized once and retains value.
- extern: declaration refers to a global object defined elsewhere.
- register: requests register storage; its address cannot be taken with `&`.
