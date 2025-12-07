This document defines the design standards applied across all Magic Forge hardware and PCB designs. It ensures consistency, manufacturability, and traceability, and aligns with ISO 9001:2015 Clause 8.3 (Design and Development).

---

## 📐 PCB Design Standards

| Parameter | Standard | Notes |
|----------|----------|-------|
| Minimum signal via diameter | .559mm x 0.254mm | design requirements may use different sizes |
| Minimum power via diameter  | .813mm x 0.457mm | design requirements may use different sizes |
| Minimum trace width | 0.127mm | Based on 1 oz copper, adjusted for current |
| Minimum trace spacing | 0.203mm | IPC Class II compliant |
| Via-to-pad clearance | 0.15mm | Ensures solder mask integrity |
| Polygon pour clearance | 0.203mm | Ensures clean spacing between polygons |
| Ground pour clearance | 0.203mm | Prevents unintentional shorts |
| Silkscreen font size | ≥ 0.635mm x .127mm | Ensures legibility post-fabrication |
| Mounting hole diameter | 3.2mm | Standard for M3 screws |
| Board edge clearance | ≥ 0.5mm | Prevents copper exposure at edge |

---

## 🔧 Schematic Standards

- All components must have reference designators and value labels
- Power nets must be clearly labeled (`VCC`, `GND`, `VBAT`, etc.)
- Decoupling capacitors must be placed within 5 mm of IC power pins
- Symbols must follow IEC or ANSI standards where applicable

---

## 🧠 Symbolic Design Considerations

- Timestamping logic must be modular and traceable
- Symbolic overlays (if used) must be documented in `design_log.md`
- All symbolic elements must be testable or explainable in deployment context

---

## 📁 ISO Clause Mapping

| ISO Clause | Description | This Document Section |
|------------|-------------|------------------------|
| 7.1        | Resources | PCB and schematic standards |
| 7.5        | Documented information | Entire document, Git history |
| 8.3        | Design and development | All sections |
| 8.5        | Production and service provision | PCB standards for fabrication |
| 9.1        | Monitoring and measurement | Trace width vs. current validation |
| 10.2       | Nonconformity and corrective action | Deviations logged in `design_log.md` |

---

---

## PCB Fabrication Notes Starter

* Copy/Paste this into a text box in the PCB editor on a fabrication/user layer and edit to match board requirements.

NOTES: UNLESS OTHERWISE SPECIFIED.

1. FABRICATE PER IPC-6012A CLASS 2.
2. FOR BOARD THICKNESS AND IMPEDANCE DETAILS REFER STACKUP DOCUMENT.
3. PRINTED WIRING BOARD SHALL COMPLY WITH REQUIREMENTS OF ANSI/J-STD-003.
4. SURFACE FINISH: IMMERSION SILVER
5. SOLDERMASK ON BOTH SIDES OF THE BOARD SHALL BE LPI, COLOR XXXXXX.
6. SILK SCREEN LEGEND TO BE APPLIED PER LAYER STACKUP USING WHITE NON-CONDUCTIVE EPOXY INK.
7. THIS PRINTED WIRING BOARD IS DESIGNED WITH A MINIMUM CONDUCTOR WIDTH AND SPACING OF 4 MIL & 4 MILS.
8. ALL VIAS ARE TENTED ON BOTH SIDES UNLESS SOLDERMASK OPENED IN GERBER.
9. ALL VIAS ON PAD SHOULD BE FILLED WITH NON CONDUCTIVE EPOXY AND SURFACE SHOULD BE FLAT. FLATNESS TOLERANCE FOR VIA ON PADS: +0.000 /- 0.001 INCHES ON BOTH SIDES. THE MANUFACTURER IS REQUESTED TO SIZE PER THEIR SOLDERMASK TOLERANCE.
10. SOLDER MASK OPENING IS KEPT SAME SIZE AS PAD (1:1) FOR ALL COMPONENTS
11. VENDOR SHOULD FOLLOW ROHS COMPLIANT PROCESS AND Pb FREE FOR MANUFACTURING
12. MANUFACTURER'S IDENTIFICATION, DATECODE LETTER SHALL BE SILKSCREENED ON SOLDER SIDE OF THE BOARD.
13. TRACE WIDTH SHOULD BE ACCURATELY ETCHED. MAX TOLERANCE +/- 1 MIL
14. ALL DIMENSIONS ARE IN INCHES UNLESS OTHERWISE SPECIFIED.
15. FLATNESS REQUIREMENTS:
A. BOW AND TWIST OF ASSEMBLY SUB-PANEL OR SINGULATED PWB SHALL NOT EXCEED 0.7% OF LONGEST SIDE
B. TEST IN ACCORDANCE WITH THE CURRENT REVISION OF IPC-TM-650 2.4.22
16. PCB MATERIAL REQUIREMENTS:
A. FLAMMABILITY RATING MUST MEET OR EXCEED UL94V-0 REQUIREMENTS. PCB MUST BEAR THE UL94V-0 REGISTERED MATERIAL ID NUMBER.
B. Tg XXXXX C OR EQUIVALENT.
C. EQUIVALENT MATERIAL SHALL BE RoHS COMPLIANT, HALOGEN FREE AND APPROVED BY ABC-Corp.
17. LAYER TO LAYER REGISTRATION SHALL BE WITHIN +/-2 MIL
18. FOR ETCHING TOLERANCE ON REF-DES XXXXX, REFER to "XXXXX ETCHING REQUIREMENTS" DOCUMENT.
19. IMPEDANCE CONTROL REQUIREMENTS (ALL TOLERANCES +/- 10%):
A. ALL 0.nn MM WIDE SINGLE-END TRACES ON LAYER X SHALL BE 50 OHMS.
B. ALL 0.nn MM WIDE/0.nn MM SPACE PAIRS ON LAYER Y SHALL BE 90 OHMS.
C. ALL 0.nn MM WIDE/0.nn MM SPACE PAIRS ON LAYER Z SHALL BE 90 OHMS.
D. VENDOR MAY ADJUST DESIGN GEOMETRIES UP TO +/-20% TO ACHIEVE TARGET IMPEDANCE. ADJUSTMENTS BEYOND 20% OF LINE WIDTH, SPACING OR DIELECTRIC THICKNESS SHALL REQUIRE APPROVAL FROM ABC-Corp ENGINEERING.


## 🔄 Update Procedure

This document is reviewed:
- Before each new PCB revision
- During quarterly QMS reviews
- When fabrication feedback indicates needed changes

Commit messages for updates should follow:
```bash
git commit -m "Updated design_standards.md — adjusted trace width for 2A current paths"
