"""
orientation.py
功能：计算牙齿朝向
作者：邓力源
联系方式: 1762062484@qq.com
创建日期：2025-4-23
"""
import average_normal
import slice_centroid_compute

def calculate_orientation(file_path, FDI_index):
    
    根据FDI编号选择不同的计算方法
    if FDI_index % 10 < 6:
        return slice_centroid_compute.slice_centoid(file_path)
    else:
        return average_normal.average_normal(file_path)
  

if __name__ == "__main__":
    file_path = r"E:\MylabProjects\jiuweidao\wzpdata\teeth2\source\teeth8.ply"
    FDI_index = 12
    orientation = calculate_orientation(file_path, FDI_index)
    print(f"牙齿 {FDI_index} 的朝向向量为: {orientation}")
