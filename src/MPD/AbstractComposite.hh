#ifndef FREYA_ABSTRACT_COMPOSITE
#define FREYA_ABSTRACT_COMPOSITE

#include <vector>

namespace MPD
{
class AbstractComposite
{
public:

    AbstractComposite(bool is_leaf)
    {
        m_IsLeaf = is_leaf;
    }
    virtual ~AbstractComposite() {}
    /**
     * @brief Wether this item is a leaf of the Compositum
     *
     * If false, it it's a container
     *
     * @return
     */
    bool is_leaf()
    {
        return m_IsLeaf;
    }
    /**
     * @brief Get the Path to this item
     *
     * @return
     */
    virtual const char * get_path() = 0;

private:
    bool m_IsLeaf;
};
}

#endif /* end of include guard: FREYA_ABSTRACT_COMPOSITE */
