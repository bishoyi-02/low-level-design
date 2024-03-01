class Singleton{
    // default constructor can't be called in driver code
    protected:
        Singleton()=default;
        Singleton(Singleton&)=delete // prevent cloning
    public:
        static Singleton& getInstance(){
            static Singleton instance; // same instance will be returned on subsequent calls
            return instance; 
        }
};

main (){
    Singleton &singleton = Singleton::getInstance();
}