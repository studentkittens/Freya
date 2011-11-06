/* Singleton macro. Taken from the C-Wikibooks pages:
 * http://de.wikibooks.org/wiki/C++-Programmierung:_Entwurfsmuster:_Singleton
 */

#define DEF_SINGLETON( NAME )    \
 public:                         \
    static NAME& instance()      \
    {                            \
       static NAME _instance;    \
       return _instance;         \
    }                            \
 private:                        \
    NAME();                      \
    NAME(const NAME&);
