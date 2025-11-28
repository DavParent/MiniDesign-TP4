#pragma once
#include <vector>

class Surface {
public:
    Surface() = default;
    explicit Surface(const std::vector<int>& pointIds)
        : pointIds_(pointIds) {}

        const std::vector<int>& getPointIds() const { return pointIds_; }
        void setPointIds(const std::vector<int>& ids) { pointIds_= ids; }

private:
    std::vector<int> pointIds_;
}