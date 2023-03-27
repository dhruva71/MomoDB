use pyo3::prelude::*;
use datastore::datastore::DataStore;

#[pyclass]
struct PyDataStore {
    data: DataStore,
}

#[pymethods]
impl PyDataStore {
    #[new]
    fn new() -> Self {
        Self {
            data: DataStore::new(),
        }
    }

    fn put(&mut self, key: String, value: String) {
        self.data.put(key, value);
    }

    fn get(&self, key: &str) -> Option<String> {
        self.data.get(key)
    }

    fn delete(&mut self, key: &str) {
        self.data.delete(key);
    }
}

#[pymodule]
fn pymomodb(_py: Python, m: &PyModule) -> PyResult<()> {
    m.add_class::<PyDataStore>()?;
    Ok(())
}
