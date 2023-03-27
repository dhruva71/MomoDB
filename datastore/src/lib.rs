pub mod datastore {
    use std::collections::HashMap;

    pub struct DataStore {
        data: HashMap<String, String>,
    }

    impl DataStore {
        // Creates a new empty datastore
        pub fn new() -> Self {
            Self {
                data: HashMap::new(),
            }
        }

        // Adds a key-value pair to the datastore
        pub fn put(&mut self, key: String, value: String) {
            self.data.insert(key, value);
        }

        // Retrieves the value associated with a given key, if it exists
        pub fn get(&self, key: &str) -> Option<String> {
            self.data.get(key).cloned()
        }

        // Removes a key-value pair from the datastore by its key
        pub fn delete(&mut self, key: &str) {
            self.data.remove(key);
        }
    }
}
