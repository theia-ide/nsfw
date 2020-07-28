declare module '@theia/nsfw' {

    export = NSFW;

    /**
     * Returns a Promise that resolves to the created NSFW Object.
     * @param {watchPath} watchPath - the path that nsfw should watchPath
     * @param {eventCallback} eventCallback - callback that will be fired when NSFW has change events
     * @param {options} options - options
     */
    function NSFW(watchPath: string, eventCallback: (events: Array<NSFW.FileChangeEvent>) => void, options?: Partial<NSFW.Options>): Promise<NSFW.NSFW>;
    namespace NSFW {

        export interface NSFW {
            /** Returns a Promise that resolves when the NSFW object has started watching the path. */
            start: () => Promise<void>;
            /** Returns a Promise that resolves when NSFW object has halted. */
            stop: () => Promise<void>;
        }

        export interface Options {
            /** time in milliseconds to debounce the event callback */
            debounceMS?: number;
            /** callback to fire in the case of errors */
            errorCallback: (err: any) => void;
            /** js regex array to filter which path to watch or not */
            ignorePathRegexArray: string[];
        }

        /** mapping object representing all the ActionType enum values */
        export const actions: typeof NSFW.ActionType;

        export const enum ActionType {
            CREATED = 0,
            DELETED = 1,
            MODIFIED = 2,
            RENAMED = 3
        }

        export type CreatedFileEvent = GenericFileEvent<ActionType.CREATED>;
        export type DeletedFileEvent = GenericFileEvent<ActionType.DELETED>;
        export type ModifiedFileEvent = GenericFileEvent<ActionType.MODIFIED>;
        export interface RenamedFileEvent extends BaseFileEvent {
            action: ActionType.RENAMED;
            /** the name of the file before a rename */
            oldFile: string;
            /** the new location of the file(only useful on linux) */
            newDirectory: string;
            /** the name of the file after a rename */
            newFile: string;
        }
        export type FileChangeEvent = CreatedFileEvent | DeletedFileEvent | ModifiedFileEvent | RenamedFileEvent;

        interface GenericFileEvent<T extends ActionType> extends BaseFileEvent {
            action: T;
            /** the name of the file that was changed(Not available for rename events) */
            file: string;
        }

        interface BaseFileEvent {
            /** the type of event that occurred */
            action: ActionType;
            /** the location the event took place */
            directory: string;
        }
    }
}
