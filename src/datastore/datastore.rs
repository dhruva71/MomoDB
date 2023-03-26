pub mod datastore {
    use std::collections::HashMap;

    pub struct DataStore {
        data: HashMap<String, String>,
    }

    impl DataStore {
        pub fn new() -> DataStore {
            DataStore {
                data: HashMap::new(),
            }
        }

        pub fn put(&mut self, key: &str, value: &str) {
            self.data.insert(key.to_string(), value.to_string());
        }

        pub fn get(&self, key: &str) -> Option<&String> {
            self.data.get(key)
        }

        pub fn delete(&mut self, key: &str) {
            self.data.remove(key);
        }
    }
}