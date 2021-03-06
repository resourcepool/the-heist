import { AccessLevelEnum } from './access-level.enum';

export interface Employee {
    userId: string;
    firstName: string;
    lastName: string;
    accessLevel: AccessLevelEnum;
    dateOfBirth: number[];
    dateOfHiring: number[];
    lastLogin: number[];
}
