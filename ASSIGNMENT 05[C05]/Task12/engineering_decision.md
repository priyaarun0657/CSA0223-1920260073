# Engineering decision
Use modular functions and a growable donor list for the current scale; store donor records in text for maintainability and stock in a fixed-record binary file for fast updates. For production, validate serialization, back up data, and measure realistic workloads. A sorted index or batch scan may be preferred as data grows.
