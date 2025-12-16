### Standard Operating Procedure — Incoming Inspection of Materials

**Document ID:** SOP-INSP-001  
**Owner:** Manufacturing Lead  
**Version:** 1.0  
**Date:** 2025-12-13

---

### Purpose and Scope

**Purpose:**  
Define the standardized process for receiving, inspecting, documenting, and dispositioning incoming materials used in any products by OurCompanyHere.

**Scope:**  
Applies to all incoming components, PCBs, assemblies, mechanical parts, and consumables received for prototype and small‑batch production.

---

### Roles and Responsibilities

| Role | Responsibilities |
| --- | --- |
| Manufacturing Lead | Oversees incoming inspection process; approves final disposition |
| QA Lead | Reviews inspection results; handles nonconformances and escalations |
| Procurement | Ensures POs reference approved suppliers; provides CoC and documentation |
| Receiving Technician | Performs visual, mechanical, and electrical checks; logs results |
| Design Lead | Supports evaluation of technical or borderline acceptance cases |

---

### Required Documents and Tools

| Item | Description |
| --- | --- |
| MDL-004 | Incoming Inspection & FAI Checklist |
| MDL-014 | Approved Supplier List |
| MDL-006 | Nonconformance & CAPA Log |
| Calibrated Tools | Calipers, multimeter, microscope, scale, etc. |
| Supporting Docs | CoC, datasheets, drawings, PCB stackup, MPN verification |

---

### Incoming Inspection Workflow

1. **Receive Shipment**  
   - Verify package integrity.  
   - Compare shipment to PO (quantity, part numbers, supplier).  
   - Move items to “Incoming Inspection” area.

2. **Documentation Check**  
   - Confirm supplier is listed in MDL‑014.  
   - Verify Certificate of Conformance (CoC) or test report.
   - Record lot number or supplier batch ID and date code.

3. **Visual Inspection**  
   - Check for physical damage, contamination, bent pins, oxidation, or incorrect labeling.  
   - For PCBs: inspect solder mask, silkscreen, drill alignment, warpage.

4. **Dimensional Inspection**  
   - Measure critical dimensions using calipers or microscope.  
   - Compare against datasheet or drawing tolerances.

5. **Electrical Inspection (if applicable)**  
   - Spot‑check resistance, continuity, or voltage rating.  
   - For modules: verify correct labeling and revision.

6. **Quantity Verification**  
   - Count or weigh components to confirm quantity matches PO.

7. **Record Results**  
   - Log findings in the Incoming Inspection Log.  
   - Attach photos for any anomalies.  
   - Store results in `/logs/Incoming Inspection Logs/MDL-004_Incoming_Inspection.xlxs`.

8. **Disposition**  
   - **Accept:** Meets all requirements → move to “Approved Inventory.”  
   - **Conditional Accept:** Minor issues; requires QA approval. Upon QA approval to accept the deviation, a physical note must remain with the approved inventory indicating the approval date, the NCM number, and who it was approved by until the final quantity is consumed. Approved materials should take priority over FIFO where possible.
   - **Reject:** Nonconforming → quarantine. NCM number follows the unit until final disposition.

* All NCM and their dispositions are logged in `/logs/Non Conforming/MDL‑006_NCM_Log.xlxs`.
* To create the NCM number, use the current MMDDYY-XXXX where XXXX is the sequence the entry was made in. Example, 121525-0001 would be for an NCM generated on December 15th 2025 and is the first one generated on that date.

---

### Inspection Criteria

| Category | Inspection Requirements |
| --- | --- |
| Passive Components | Correct MPN, value, tolerance, packaging integrity |
| ICs / Modules | Correct revision, labeling, no bent pins, ESD packaging intact |
| PCBs | Layer count, thickness, finish, drill quality, solder mask alignment |
| Mechanical Parts | Dimensions within tolerance, surface finish, no burrs |
| Assemblies | Solder quality, polarity, component placement, cleanliness |

---

### Nonconformance Handling

| Step | Action |
| --- | --- |
| Identify | Mark item as “Hold – NCM” and move to quarantine area |
| Record | Log issue in MDL‑006 with photos and lot details |
| Evaluate | QA Lead reviews severity and determines disposition |
| Corrective Action | Supplier contacted if required; CAPA opened for repeated issues |
| Final Disposition | Accept, rework, return to supplier, or scrap |

---

### Records and Retention

| Record | Location | Retention |
| --- | --- | --- |
| Incoming Inspection Log | /docs/MDL-004_Incoming_Inspection_FAI.md | 7 years |
| Supplier CoC / Test Reports | /procurement/supplier-docs/ | 7 years |
| NCM / CAPA Records | /docs/MDL-006_Nonconformance_CAPA.md | 7 years |
| Photos & Evidence | /test/test-logs/incoming/ | 7 years |

---

### KPIs

| KPI | Target |
| --- | --- |
| Lot Acceptance Rate | > 98% |
| Inspection Turnaround Time | < 48 hours |
| Supplier-Related NCMs | < 2 per quarter |
| Repeat Supplier Issues | 0 repeats within 12 months |

---

### Revision History

| Version | Date | Author | Summary |
| --- | --- | --- | --- |
| 1.0 | 2025-12-13 | Manufacturing Lead | Initial SOP for incoming inspection |
