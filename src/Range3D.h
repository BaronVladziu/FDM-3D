//
// Created by baronvladziu on 21.11.18.
//

#ifndef VULKAN_FDM_RANGE3D_H
#define VULKAN_FDM_RANGE3D_H


class Range3D {

    float _minX = 0.f;
    float _minY = 0.f;
    float _minZ = 0.f;
    float _maxX = 0.f;
    float _maxY = 0.f;
    float _maxZ = 0.f;

public:
    Range3D() = default;
    Range3D(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
    float getMaxX() const;
    float getMaxY() const;
    float getMaxZ() const;
    float getMinX() const;
    float getMinY() const;
    float getMinZ() const;
    void setMaxX(float v);
    void setMaxY(float v);
    void setMaxZ(float v);
    void setMinX(float v);
    void setMinY(float v);
    void setMinZ(float v);
    Range3D operator+(const Range3D & range) const;
    Range3D & operator=(const Range3D & range);
    void operator+=(const Range3D & range);

private:
    float min(float a, float b) const;
    float max(float a, float b) const;

};


#endif //VULKAN_FDM_RANGE3D_H
