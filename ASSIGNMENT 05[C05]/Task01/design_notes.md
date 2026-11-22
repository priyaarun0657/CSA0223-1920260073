# A1.3 Global variables alternative
Global shared arrays reduce parameter passing but increase coupling, make tests depend on hidden state, and prevent reuse with independent datasets. Runtime and storage asymptotically remain the same; the design becomes less maintainable.
