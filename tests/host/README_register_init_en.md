# Register initialization generator Host regressions

From the repository root, run with Python 3.8 or newer (standard library only):

```bash
python3 tests/host/test_register_init_short_pairs.py
```

The tests read real isolated reginfo files through `process_reginfo`, exercising
AIC and AIV records with 2/3/4-field high debug address lines. They verify that
all eight normal and four valid debug registers survive an incomplete pair,
and retain existing handling of absent, blank, unrelated, and invalid-hex
companion records. Each temporary directory is cleaned after use.

The CLI regression runs the actual script in a separate temporary directory
with both file types and checks the generated C++ text and processing log.
These tests validate Host parsing and generation. They do not compile Runtime,
the generated C++ fragment, or execute device register collection.

The regression is also registered in `runtime_api_stub_generator_ut`; run it from an existing UT build with `cmake --build <build-dir> --target runtime_api_stub_generator_ut`.
