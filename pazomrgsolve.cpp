[PROB]

# Annotated model
  - Author: Z.TAN
  - drug: Pazopanib
  - model_ref: Tan et al, PAGE2023 10553
  - Structure: one compartment, first order absorption
  - Implementation: closed form solutions
  - Error model: Additive + proportional
  - Covariates:
    - DOSE on F1
  - Random effects on: `CL`, `V`, `F1`


[PARAM] @annotated
TVCL : 0.498 : Clearance (L/hr)
TVV  : 43.8  : Volume of distribution (L)
TVKA : 0.976 : Absorption rate constant (1/hr)
TVF1 : 1     : Bioavailability
FCOV : 0.42  : POWER on F1


ETA1 : 0 : ETA on CL
ETA2  : 0 : ETA on VC
ETA3 : 0 : ETA on F1


$PARAM @covariates @annotated
AOLA : 200 : default dose


[CMT] @annotated 
GUT : Depot compartment [ADM]
CENT : Central compartment (mg/L)[OBS]

[MAIN] 
double CL = TVCL * exp(ETA1+ETA(1)) ;
double V = TVV * exp(ETA2+ETA(2)) ;
double KA = TVKA ;
double F1 = TVF1 * exp(ETA3+ETA(3)) * pow(200/AOLA,FCOV) ;
F_GUT = F1 ;

[OMEGA]
0.0412 
0.538
0.075

[SIGMA] @annotated
PROP: 0.24 : Proportional residual error
ADD : 4.59 : Additive residual error

[PKMODEL] ncmt=1, depot=TRUE

[TABLE]

double DV = (CENT/V)*(1+PROP) + ADD;


$CAPTURE @annotated
DV : Pazopanib concentration central (mg/L)
