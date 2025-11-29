#pragma once

class NuageElement {
protected:
    int m_id;
    
    explicit NuageElement(int id) : m_id(id) {}
    
public:
    virtual ~NuageElement() = default;
    
    int getId() const { return m_id; }
};
