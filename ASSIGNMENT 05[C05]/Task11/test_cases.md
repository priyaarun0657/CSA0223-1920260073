# Validation cases
- Age 17 and 90 days: reject (age boundary)
- Age 18 and 89 days: reject (donation interval boundary)
- Age 18 and 90 days: accept
- Age 60 and 365 days: accept
- Invalid group and negative units: reject at CLI validation
