declare module "@sqlite.org/sqlite-wasm" {
  // biome-ignore lint/suspicious/noExplicitAny: <explanation>
  type TODO = any;

  /**
   * A function to be called when the SQLite3 module and worker APIs are done
   * loading asynchronously. This is the only way of knowing that the loading
   * has completed.
   *
   * @since V3.46: Is passed the function which gets returned by
   *   `sqlite3Worker1Promiser()`, as accessing it from this callback is more
   *   convenient for certain usage patterns. The promiser v2 interface obviates
   *   the need for this callback.
   */
  type OnreadyFunction = () => void;

  type Sqlite3Worker1PromiserConfig = {
    onready?: OnreadyFunction;
    /**
     * A worker instance which loads `sqlite3-worker1.js`, or a functional
     * equivalent. Note that the promiser factory replaces the
     * `worker.onmessage` property. This config option may alternately be a
     * function, in which case this function is called to instantiate the
     * worker.
     */
    worker?: Worker | (() => Worker);
    /** Function to generate unique message IDs */
    generateMessageId?: (messageObject: TODO) => string;
    /**
     * A `console.debug()` style function for logging information about Worker
     * messages.
     */
    // biome-ignore lint/suspicious/noExplicitAny: <explanation>
    debug?: (...args: any[]) => void;
    /**
     * A callback function that is called when a `message` event is received
     * from the worker, and the event is not handled by the proxy.
     *
     * @note This *should* ideally never happen, as the proxy aims to handle
     * all known message types.
     */
    onunhandled?: (event: MessageEvent) => void;
  };

  /**
   * A db identifier string (returned by 'open') which tells the operation which
   * database instance to work on. If not provided, the first-opened db is
   * used.
   *
   * @warning This is an "opaque" value, with no inherently useful syntax
   * or information. Its value is subject to change with any given build
   * of this API and cannot be used as a basis for anything useful beyond
   * its one intended purpose.
   */
  type DbId = string | undefined;
  type Sqlite3Version = {
    libVersion: string;
    sourceId: string;
    libVersionNumber: number;
    downloadVersion: number;
  };

  // Message types and their corresponding arguments and results. Should be able to get better types for some of these (open, exec and stack) from the existing types, although the Promiser verions have minor differences
  type PromiserMethods = {
    /** @link https://sqlite.org/wasm/doc/trunk/api-worker1.md#method-open */
    open: {
      args: Partial<
        {
          /**
           * The db filename. [=":memory:" or "" (unspecified)]: TODO: See the
           * sqlite3.oo1.DB constructor for peculiarities and transformations
           */
          filename?: string;
        } & {
          /**
           * Sqlite3_vfs name. Ignored if filename is ":memory:" or "". This may
           * change how the given filename is resolved. The VFS may optionally
           * be provided via a URL-style filename argument: filename:
           * "file:foo.db?vfs=...". By default it uses a transient database,
           * created anew on each request.
           *
           * If both this argument and a URI-style argument are provided, which
           * one has precedence is unspecified.
           */
          vfs?: string;
        }
      >;
      result: {
        dbId: DbId;
        /** Db filename, possibly differing from the input */
        filename: string;
        /**
         * Indicates if the given filename resides in the known-persistent
         * storage
         */
        persistent: boolean;
        /** Name of the underlying VFS */
        vfs: "string";
      };
      /** @link https://sqlite.org/wasm/doc/trunk/api-worker1.md#method-close */
    };
    close: {
      args: { dbId?: DbId };
      result: {
        /** Filename of closed db, or undefined if no db was closed */
        filename: string | undefined;
      };
      /** @link https://sqlite.org/wasm/doc/trunk/api-worker1.md#method-config-get */
    };
    "config-get": {
      args: unknown;
      result: {
        dbID: DbId;
        version: Sqlite3Version;
        /** Indicates if BigInt support is enabled */
        bigIntEnabled: boolean;
        /** Indicates if opfs support is enabled */
        opfsEnabled: boolean; //not documented on sqlie.org?
        /** Result of sqlite3.capi.sqlite3_js_vfs_list() */
        vfsList: string[]; // is there a full list somewhere I can use?
      };
    };
    /**
     * Interface for running arbitrary SQL. Wraps`oo1.DB.exec()` methods. And
     * supports most of its features as defined in
     * https://sqlite.org/wasm/doc/trunk/api-oo1.md#db-exec. There are a few
     * limitations imposed by the state having to cross thread boundaries.
     *
     * @link https://sqlite.org/wasm/doc/trunk/api-worker1.md#method-exec
     */
    exec: {
      args: {
        sql: string;
        dbId?: DbId;
        /**
         * At the end of the result set, the same event is fired with
         * (row=undefined, rowNumber=null) to indicate that the end of the
         * result set has been reached. Note that the rows arrive via
         * worker-posted messages, with all the implications of that.
         */
        callback?: (result: {
          /**
           * Internally-synthesized message type string used temporarily for
           * worker message dispatching.
           */
          type: string;
          /** Sqlilte3 VALUE */
          row: TODO;
          /** 1-based index */
          rowNumber: number;
          columnNames: string[];
        }) => void;
        /**
         * A single value valid as an argument for Stmt.bind(). This is only
         * applied to the first non-empty statement in the SQL which has any
         * bindable parameters. (Empty statements are skipped entirely.)
         */
        bind?: Exclude<TODO, null>;
        [key: string]: TODO; //
      };
      result: { [key: string]: TODO };
    };
  };

  type PromiserResponseSuccess<T extends keyof PromiserMethods> = {
    /** Type of the inbound message */
    type: T;
    /** Operation dependent result */
    result: PromiserMethods[T]["result"];
    /** Same value, if any, provided by the inbound message */
    messageId: string;
    /**
     * The id of the db which was operated on, if any, as returned by the
     * corresponding 'open' operation.
     */
    dbId: DbId;
    // possibly other metadata ...
    /* 
    WorkerReceivedTime: number
    WorkerRespondTime: number
    departureTime: number
     */
  };

  type PromiserResponseError = {
    type: "error";
    /** Operation independent object */
    result: {
      /** Type of the triggereing operation */
      operation: string;
      /** Error Message */
      message: string;
      /** The ErrorClass.name property from the thrown exception */
      errorClass: string;
      /** The message object which triggered the error */
      input: object;
      /** _if available_ a stack trace array */
      stack: TODO[];
    };
    /** Same value, if any, provided by the inbound message */
    messageId: string;
    dbId: DbId;
  };
  type PromiserResponse<T extends keyof PromiserMethods> = PromiserResponseSuccess<T> | PromiserResponseError;

  type Promiser = {
    <T extends keyof PromiserMethods>(
      /** The type of the message */
      messageType: T,
      /** The arguments for the message type */
      messageArguments: PromiserMethods[T]["args"]
    ): Promise<PromiserResponse<T>>;

    <T extends keyof PromiserMethods>(message: {
      /** The type of the message */
      type: T;
      /** The arguments for the message type */
      args: PromiserMethods[T]["args"];
    }): Promise<PromiserResponse<T>>;
  };

  /** Factory for creating promiser instances. */
  const sqlite3Worker1Promiser: {
    /**
     * Promiser v1
     *
     * @example
     *   const factory = sqlite3Worker1Promiser({
     *     onready: () => {
     *       promiser('open', { filename: 'my_database.sqlite' })
     *         .then((msg) => {
     *           // ...
     *         })
     *         .catch((e) => {
     *           console.error(e);
     *         });
     *     },
     *   });
     *
     * @link https://sqlite.org/wasm/doc/trunk/api-worker1.md#promiser
     */
    (config?: Sqlite3Worker1PromiserConfig | OnreadyFunction): Promiser;

    /**
     * Promiser v2
     *
     * @since 3.46:
     * @example
     *   const factoryPromise = sqlite3Worker1Promiser.v2(config);
     *   const factory = await factoryPromise;
     *
     * @link https://sqlite.org/wasm/doc/trunk/api-worker1.md#promiser.v2
     */
    v2: (config?: Sqlite3Worker1PromiserConfig | OnreadyFunction) => Promise<Promiser>;
    defaultConfig: Sqlite3Worker1PromiserConfig;
  };
}
