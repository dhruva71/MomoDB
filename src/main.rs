use datastore::datastore::DataStore;

fn main() {
    let mut store = DataStore::new();

    // Store a value
    store.put("foo".to_string(), "bar".to_string());
    let value = store.get("foo").unwrap();
    println!("Value of foo: {}", value);
    store.delete("foo");

    // This will fail because the value is no longer in the store
    println!("Value of foo: {:?}", store.get("foo"));
}
