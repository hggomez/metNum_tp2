# OCR with KNN and PCA

Objective: manually implement PCA and Knn to recognize handwritten numerical digits.

The main challenge within PCA is finding the eigenvalues of the covariance matrix. The power iteration method gives us the highest eigenvalue with its associated eigenvector, however we need to find every eigenvalue of the given matrix. In order to do this we use a deflation method, which modifies the matrix replacing the maximum eigenvalue by zero and enabling us to extract another pair of eigenvalue and eigenvector.
