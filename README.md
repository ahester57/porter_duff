# Porter-Duff Operators
### Austin Hester
### CS 6420 - Computer Vision
### UMSL SP2021, Prof. Sanjiv Bhatia

----
## Purpose

The purpose of this assignment is to implement the Porter-Duff operators for composition of images. The operators will be
tested by a driver program.

----

## Image Highlighting

Image highlighting is generally used to bring attention of a viewer to a specific area of an image while dimming the rest of the
image to provide context.

#### Task

Porter-Duff operators are used for composition of images with binary masks. Their most common use is in green screen
normally used for weather telecasts. The binary masks define the support of pixels in each input image. The pixels that
contribute in the composition of final images are known as valid pixels and are indicated by 1 (or 0XFF); the remaining pixels
are called invalid pixels and are indicated by 0. Invalid pixels are ignored.

In the following table, the Porter-Duff operators [1] are defined for images I1 and I2 while their corresponding masks are
defined by M1 and M2.

Operation Implementation Ir Mask Mr  
clear 0 0  
copy I1 I1 M1  
I1 over I2 (I1 ∧ M1) ∨ (I2 ∧ M2 ∧ ¬M1) M1 ∨ M2  
I1 in I2 I1 M1 ∧ M2  
I1 out I2 I1 M1 ∧ ¬M2  
I1 atop I2 (I1 ∧ M1) ∨ (I2 ∧ ¬M2) M2  
I1 xor I2 (I1 ∧ M1 ∧ ¬M2) ∨ (I2 ∧ ¬M1 ∧ M2) (M1 ∧ ¬M2) ∨ (¬M1 ∧ M2)  

Your task is to define functions corresponding to each of the Porter-Duff operators and test the output using a driver program
as described in the implementation steps.

----

#### Usage

```
Usage: porter-duff.exe [params]

        -g, --grayscale
                read grayscale
        -h, --help (value:true)
                show help message
        --i1, --image1 (value:<none>)
                input image
        --i2, --image2 (value:<none>)
                input image
        --m1, --mask1 (value:<none>)
                input image
        --m2, --mask2 (value:<none>)
                input image

```

----

https://github.com/ahester57/porter_duff
