### Standard Operating Procedure — Non‑Conforming Materials (NCM)

**Document ID:** SOP-NCM-001  
**Owner:** QA Lead  
**Version:** 1.0  
**Date:** 2025-12-14

---

### Purpose and Scope

**Purpose:**  
Define the process for identifying, documenting, evaluating, and dispositioning non‑conforming materials (NCM) discovered during incoming inspection, in‑process assembly, testing, or field returns.

**Scope:**  
Applies to all materials, components, PCBs, assemblies, and finished units for customer consumption.

---

### Definitions

| Term | Definition |
| --- | --- |
| Non‑Conforming Material (NCM) | Any item that does not meet specifications, drawings, BOM, test criteria, or purchase order requirements |
| Quarantine | Physical or digital segregation of suspect material to prevent unintended use |
| CAPA | Corrective and Preventive Action process documented in MDL‑006 |
| Disposition | Final decision for handling NCM: Accept, Rework, Return to Supplier, Scrap |

---

### Roles and Responsibilities

| Role | Responsibilities |
| --- | --- |
| QA Lead | Owns NCM process, approves dispositions, opens CAPA when required |
| Manufacturing Lead | Identifies NCM during assembly or inspection, quarantines material |
| Procurement | Coordinates supplier returns and replacement orders |
| Receiving Technician | Flags NCM during incoming inspection and logs details |
| Design Lead | Provides technical evaluation for borderline or design‑related issues |

---

### When to Initiate an NCM Record

An NCM record must be created when any of the following occur:

- Incoming inspection failure  
- Incorrect MPN, revision, or supplier  
- Damaged, contaminated, or mislabeled parts  
- PCB defects (mask misalignment, drill issues, warpage)  
- Assembly defects (solder bridges, missing components, polarity errors)  
- Failed electrical tests or functional tests  
- Field return with confirmed defect  
- Any deviation from drawings, BOM, or specifications

---

### NCM Workflow

1. **Identify the Non‑Conformance**  
   - Stop using the material immediately.  
   - Tag item as **“Hold – NCM”**.

2. **Quarantine the Material**  
   - Move to designated NCM area (physical bin or digital folder).  
   - Prevent accidental use in production.

3. **Record the NCM**  
   - Create an entry in MDL‑006 (Nonconformance & CAPA Log).  
   - Include:  
     - Part number  
     - Supplier  
     - Lot/date code  
     - Quantity affected  
     - Description of issue  
     - Photos or measurements  
     - Discovery point (incoming, in‑process, test, field)

4. **Initial Evaluation**  
   - Manufacturing Lead and QA Lead review severity.  
   - Determine if issue is:  
     - Cosmetic  
     - Functional  
     - Safety‑critical  
     - Supplier‑related  
     - Design‑related

5. **Disposition Decision**  
   - QA Lead approves one of the following:

| Disposition | Description |
| --- | --- |
| **Accept As‑Is** | Minor deviation with no functional impact; documented justification required |
| **Rework** | Material can be corrected internally; rework instructions must be documented |
| **Return to Supplier (RTS)** | Supplier‑related defect; Procurement coordinates RMA |
| **Scrap** | Material cannot be used or reworked; must be physically destroyed or marked unusable |

6. **Execute Disposition**  
   - Rework performed by authorized personnel only.  
   - RTS items packaged and documented.  
   - Scrap items recorded and disposed per EHS guidelines.

7. **Close the NCM Record**  
   - QA Lead verifies disposition completion.  
   - Update MDL‑006 with final status and evidence.

8. **Determine Need for CAPA**  
   - Required if:  
     - Repeated supplier issues  
     - Safety‑critical failures  
     - Systemic process issues  
     - Field failures  
   - CAPA tracked in MDL‑006.

---

### Documentation Requirements

| Record | Location | Retention |
| --- | --- | --- |
| NCM Log | /docs/MDL-006_Nonconformance_CAPA.md | 7 years |
| Photos / Evidence | /test/test-logs/ncm/ | 7 years |
| Supplier RMA Docs | /procurement/supplier-docs/ | 7 years |
| Rework Instructions | /manufacturing/rework/ | 7 years |
| CAPA Records | /docs/MDL-006_Nonconformance_CAPA.md | 7 years |

---

### KPIs

| KPI | Target |
| --- | --- |
| NCM Closure Time | < 7 days for minor issues; < 14 days for major |
| Repeat Supplier NCMs | 0 repeats within 12 months |
| Scrap Rate | < 2% of total material cost |
| CAPA Effectiveness | 100% of CAPAs verified and closed |

---

### Escalation Path

1. **Manufacturing Lead → QA Lead** for all NCMs.  
2. **QA Lead → Procurement** for supplier‑related issues.  
3. **QA Lead → Quality Owner** for repeated or critical failures.  
4. **Management Review** for unresolved systemic issues.

---

### Revision History

| Version | Date | Author | Summary |
| --- | --- | --- | --- |
| 1.0 | 2025-12-14 | QA Lead | Initial SOP for non‑conforming materials |
