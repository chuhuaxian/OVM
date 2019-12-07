<p align="center">
<img src="OVM.png" width="320" />
</p>

---

# OVM-An Open Source Data Structure of Tetrahedral and Hexahedral Meshes

## Description

OVM is a scalable data structure of tetrahedral and hexahedral meshes. It is a complete open-source data structure written in C++. The features of the data structure are following:

- Efficient in both storage and time. It requires few memory since it need not to store the topological relationships of the same element, and the access of the neighbors of the same element can be achieved in constant time through a constant pre-defined array for the special structure of tetrahedral and hexahedral meshes.
- It offers dynamic properties allowing the user to attach and detach to the volumetric mesh during running time. 
- It is object-oriented using class inheritance and virtual instantiation and provides a unique interface for both tetrahedral meshes and hexahedral mesh.
- It provides local topological operations, such as face flip, split, and edge collapse operations for tetrahedral mesh.
- It is easy to understand and use for non-experts and it can be very easy to be integrated into other application projects. It offers iterators to access the elements of the mesh like C++ STL and hides the complex underlying structure with simple APIs. 

This project is created by [Chuhua Xian](http://chuhuaxian.net). Anyone who has questions can write an email to:

chuhuaxian AT gmail.com

We welcome contributions from the open-source community.

## Reference
A comprehensive description of OVM can be found in OVM_paper.pdf. 

## Tutorials
We provide several tutorials in the folder name ‘Examples’. Some volumetric mesh models are also provided in this folder.

## Documentation
The latest Documentation can be found at: OVMDoc.zip  

## Mesh Viewer
A mesh viewer is developed for viewing the tetrahedral and hexahedral mesh models. It is written in C++ and Qt5. Currently, it supports the files with the suffix of ‘.tet’, ‘.nmesh’(netgen mesh), ‘.hex’(hexahedral mesh), ‘.mesh’(MEdit), and ‘.ovm’(OVM mesh).  We give some models in the folder named 'Models'.

## Citation
We would like you citing our paper if you use OVM:
```
@article{xian2013OVM,
  title={OpenVolumetricMesh-An Efficient Data Structure for Tetrahedral and Hexahedral Meshes},
  author={Chuhua Xian and Guiqing Li and Shuming Gao},
  journal={Computer Aided Drafting, Design and Manufacturing},
  number={3},
  pages={5},
  year={2013}
} 
```
