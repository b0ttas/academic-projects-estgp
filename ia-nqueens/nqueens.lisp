;;;=========================================================================
;;; Escola Superior de Tecnologia e Gestão de Portalegre
;;; Ano Lectivo: 2016/2017
;;; Cadeira: Inteligência Artificial
;;; Prof. Luis Batista
;;; 2º Ano 2º Semestre
;;; Luis Carvalho nº18013
;;;=========================================================================
;;; 
;;; Prints out a "random" solution to the N-queens problem, for any N >= 4.
;;;
;;; Invoke by calling (nqueens <Board-Size>). Eg:
;;;   nqueens 4
;;;
;;;=========================================================================
;; Global Variables
(defvar *iterations* 0)
(defvar *limit* 0)
(defvar *prev_cost* -1)
;;;=========================================================================
;; Main Function call

(defun nQueens (n)
  (setf *iterations* 0) (setf *limit* 0)
  (time(init_table n)))

;;;========================================================================
;; Initialization of Array with input size (board)

(defun init_table (n)
  (rlsearch(successors(shuffle_table (fill_table (create_table n))))))

;;;========================================================================
;; Creation of Array with input size (board)

(defun create_table (n)
  (make-array n :initial-element 0))

;;;========================================================================
;; Fill Array with Queens (starting state creation)

(defun fill_table (table)
  (loop for x from 0 to (- (length table) 1) do
        (setf (aref table x) x)) table)

;;;=========================================================================
;; Shuffle Array Values

(defun shuffle_table (table)
  (loop for x from 0 to (- (length table) 1) by 1 do
        (rotatef (aref table (random (- (length table) 1))) (aref table (- (length table) 1)))) 
  (write "Estado inicial: ")(write table))

;;;=========================================================================
;;; Threat Checking

(defun threat_check (table)
  (let ((heur 0))
    (loop for x from 0 to (- (length table) 1) by 1 do
          (loop for y from (+ x 1) to (- (length table) 1) by 1 do
                (if (= (abs (- (aref table x) (aref table y))) (abs (- x y)))
                    (setf heur (+ heur 1)))))
    heur))

;; need 1 of this for squares

;;;=========================================================================
;; Successor generation

(defun create_successor (table)
  (rotatef (aref table (random (- (length table)1))) (aref table (- (length table) 1))) table)

;;;=========================================================================

(defun successors (table)
  (terpri)
  
  (let ((parent table)
        (p_threats (threat_check table))
        (child)
        (c_threats)
        (best)
        (b_threats)
        (out))
    
    (setf best (copy-seq parent))
    (setf b_threats p_threats)

    (loop for x from 0 to 10 do

      (setf child (create_successor parent))
      (setf c_threats (threat_check child))

     ;; (terpri)(write best) (write b_threats) (terpri) (write child) (write c_threats)(terpri)

      (cond
            ((eql c_threats 0) (progn (setf best (copy-seq child)) (setf b_threats c_threats) (setf out (list best b_threats)) (return-from successors out))) ;0 cost
            ((< c_threats b_threats) (progn (setf best (copy-seq child)) (setf b_threats c_threats)))))   ;lower cost

    (setf out (list best b_threats))
    out))
;;;=========================================================================
;;; Local Search

(defun lsearch (out)
  (incf *iterations*)
  (write "Ameaças ->")(write (rest out))

  (let ((i_cost (cadr out))
        (max_it (* (array-total-size (car out)) 1000)) ;test values
        (max_cost_rep (* (array-total-size (car out)) 300)))
  
    (when (= i_cost *prev_cost*) (incf *limit*))

    (setf *prev_cost* i_cost)

    (cond ((= (cadr out) 0) (end out))
          ((= *iterations* max_it) (progn (terpri)(write "Terminado, iterações máximas atingidas")(end out)))
          ((= *limit* max_cost_rep) (progn (terpri)(write "Terminado, iterações máximas c/ mesmo custo atingidas")(end out)))
          ((/= (cadr out) 0) (lsearch(successors (car out)))))))

;;;=========================================================================

(defun rlsearch (out)
  (incf *iterations*)
  (write "Ameaças ->")(write (rest out))

  (let ((i_cost (cadr out))
        (max_it (* (array-total-size (car out)) 1000)) ;test values
        (max_cost_rep (* (array-total-size (car out)) 300)))

    (when (= i_cost *prev_cost*) (incf *limit*))
    
    (setf *prev_cost* i_cost)

    (cond ((= (cadr out) 0) (end out))
          ((= *iterations* max_it) (progn (terpri)(write "Terminado, iterações máximas atingidas")(end out)))
          ((= *limit* max_cost_rep) (progn (terpri)(write "Restart")(terpri) 
                                      (setf *iterations* 0)(setf *limit* 0)(setf *prev_cost* 0)(rlsearch(successors(shuffle_table (car out))))))
          ((/= (cadr out) 0) (rlsearch(successors (car out)))))))

;;;=========================================================================
;;; Result Presentation

(defun end (out)
  (terpri)(write "ITs")(write *iterations*)(terpri)
  (write "Estado final:   ")
  (write (car out))
  (terpri)
  (cond ((/= (cadr out) 0) (progn (write "Ameaças ->") (write (cadr out))))
        ((= (cadr out) 0) (write "Solução ideal")))
  nil)